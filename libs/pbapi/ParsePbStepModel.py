#!python2
#coding:utf-8
import xml.dom.minidom
import sys
reload(sys)
sys.setdefaultencoding('utf8')


class Macro:
    def  __init__(self):
        self.ID = ""
        self.Name = ""
        self.Desc = ""
        self.Length = "64"
        self.Encrypt = "0"

class Field:
    def __init__(self):
        self.Name = ""
        self.Desc = ""
        self.Items = []

class Package:
    def __init__(self):
        self.FuncID = ""
        self.Name = ""
        self.Desc = ""
        self.Fields = []

def getMacros(macroFile):
    dom = xml.dom.minidom.parse(macroFile)
    root = dom.documentElement
    macros = {}
    for macroNode in root.getElementsByTagName("macro"):
        macro = Macro()
        macro.ID = macroNode.getAttribute("id")
        macro.Name = macroNode.getAttribute("name")
        macro.Desc = macroNode.getAttribute("desc")
        if macroNode.hasAttribute("length"):
            macro.Length = macroNode.getAttribute("length")
        if macroNode.hasAttribute("encrypt"):
            macro.Encrypt = macroNode.getAttribute("encrypt")
        macros[macro.ID] = macro
    return macros

def getFields(schemaFile, macros):
    dom = xml.dom.minidom.parse(schemaFile)
    root = dom.documentElement
    fields = {}
    fieldsNode = root.getElementsByTagName("fields")[0]
    for fieldNode in fieldsNode.getElementsByTagName("field"):
        fieldName = fieldNode.getAttribute("name")
        field = Field()
        field.Name = fieldName
        field.Desc = fieldNode.getAttribute("desc")
        for itemNode in fieldNode.getElementsByTagName("item"):
            field.Items.append(macros[itemNode.getAttribute("id")])
        fields[fieldName] = field
    return fields

def getPackages(schemaFile, fields):
    dom = xml.dom.minidom.parse(schemaFile)
    root = dom.documentElement
    packages = []
    packagesNode = root.getElementsByTagName("packages")[0]
    for packageNode in packagesNode.getElementsByTagName("package"):
        packageName = packageNode.getAttribute("name")
        package = Package()
        package.FuncID = packageNode.getAttribute("funcid")
        package.Name = packageNode.getAttribute("name")
        package.Desc = packageNode.getAttribute("desc")
        for fieldNode in packageNode.getElementsByTagName("field"):
            package.Fields.append(fields[fieldNode.getAttribute("name")])
        packages.append(package)
    return packages
	
def AddItemNode(dom, parentNode, item):
    itemNode = dom.createElement('item')
    itemNode.setAttribute("id", item.ID)
    itemNode.setAttribute("name", item.Name)
    itemNode.setAttribute("desc", item.Desc)
    itemNode.setAttribute("length", item.Length)
    itemNode.setAttribute("encrypt", item.Encrypt)
    parentNode.appendChild(itemNode)

def AddFieldNode(dom, parentNode, field):
    fieldNode = dom.createElement('field')
    fieldNode.setAttribute("name", field.Name)
    fieldNode.setAttribute("desc", field.Desc)
    for item in field.Items:
        AddItemNode(dom, fieldNode, item)
    parentNode.appendChild(fieldNode)

def AddPackageNode(dom, parentNode, package):
    packageNode = dom.createElement('package')
    packageNode.setAttribute("funcid", package.FuncID)
    packageNode.setAttribute("name", package.Name)
    packageNode.setAttribute("desc", package.Desc)
    for field in package.Fields:
        AddFieldNode(dom, packageNode, field)
    parentNode.appendChild(packageNode)

def CreatePbStepModel(destFile, macros, fields, packages):
    impl = xml.dom.minidom.getDOMImplementation()
    dom = impl.createDocument(None, 'root', None)
    root = dom.documentElement

    packagesNode = dom.createElement('packages')
    for package in packages:
        AddPackageNode(dom, packagesNode, package)
    root.appendChild(packagesNode)

    fieldsNode = dom.createElement('fields')
    for field in fields.values():
        AddFieldNode(dom, fieldsNode, field)
    root.appendChild(fieldsNode)

    f = open(destFile, 'w')
    dom.writexml(f, indent="", addindent='\t', newl='\n', encoding="utf-8")
    f.close()
	
if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: ParsePbStepModel.py destFile schema.xml macros.xml")
        exit(-1) 
    destFile = sys.argv[1]
    schemaFile = sys.argv[2]
    macrosFile = sys.argv[3]
    macros = getMacros(macrosFile)
    fields = getFields(schemaFile, macros)
    packages = getPackages(schemaFile, fields)
    print(len(packages))
    
    CreatePbStepModel(destFile, macros, fields, packages)
