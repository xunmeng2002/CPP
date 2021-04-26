#!python2
#!coding:utf-8

import xml.dom.minidom
import xml.etree.ElementTree as ET

def ParseDataType(dom, root, filename, types):
    sourceFile = open(filename, "r")
    for line in sourceFile:
        if line.startswith("typedef"):
            typeNode = dom.createElement('type')
            line = line.strip()
            items = line.split(" ")
            name = items[2][0 : items[2].rfind("Type") + 4]
            baseType = ""
            if items[1] == "short" or items[1] == "int" or items[1] == "double":
                baseType = items[1]
            elif items[1] == "char":
                if items[2].endswith("];"):
                    baseType = "string"
                    typeNode.setAttribute("size", items[2][items[2].rfind("[")+1 : items[2].rfind("]")])
                else:
                    baseType = "char"
            else:
                print line
            typeNode.setAttribute("name", name)
            typeNode.setAttribute("basetype", baseType)
            root.appendChild(typeNode)
            types[name] = baseType
    sourceFile.close()

def ParseStruct(dom, root, filename, types):
    sourceFile = open(filename, "r")
    isInstruct = False
    field = ""
    for line in sourceFile:
        line = line.strip()
        if line.startswith("};"):
            isInstruct = False  
            root.appendChild(field)
            continue
        if isInstruct:
            if line.startswith("TThostFtdc"):
                line = line.replace("\t", " ")
                items = line.split(" ")
                item = dom.createElement('item')
                item.setAttribute("name", items[1][:-1])
                item.setAttribute("type", items[0])
                item.setAttribute("basetype", types[items[0]])
                field.appendChild(item)
        elif line.startswith("struct"):
            isInstruct = True
            field = dom.createElement('field')
            fieldName = line.split(" ")[1]
            shortName = fieldName[10 : fieldName.rfind("Field")]
            field.setAttribute("name", fieldName)
            field.setAttribute("shortname", shortName)

    sourceFile.close()

def ParseFuncParams(dom, func, line):
    paramsString = line[line.find("(")+1 : line.rfind(")")]
    if len(paramsString) == 0:
        return
    items = paramsString.split(",")
    for item in items:
        item = item.strip()
        attributes = item.split(" ")
        type = attributes[0]
        name = attributes[1]
        custom = "False"
        if type.startswith("CThostFtdc"):
            custom = "True"
            name = type[10 : type.rfind("Field")]
        param = dom.createElement('param')
        param.setAttribute("type", type)
        param.setAttribute("name", name)
        param.setAttribute("custom", custom)
        func.appendChild(param)

def ParseFuncAttrib(dom, root, line):
    items = line.split(" ")
    func = dom.createElement('func')
    func.setAttribute("return", items[1])
    func.setAttribute("name", items[2][0 : items[2].find("(")])
    if items[2].startswith("OnErrRtn"):
        func.setAttribute("type", "OnErrRtn")
    elif items[2].startswith("OnRtn"):
        func.setAttribute("type", "OnRtn")
    elif items[2].startswith("OnRspQry"):
        func.setAttribute("type", "OnRspQry")
    elif items[2].startswith("OnRsp"):
        func.setAttribute("type", "OnRsp")
    elif items[2].startswith("On"):
        func.setAttribute("type", "On")
    else:
        func.setAttribute("type", "None")
    ParseFuncParams(dom, func, line)
    root.appendChild(func)

def ParseSpiFunc(dom, root, filename):
    sourceFile = open(filename, "r")
    isInclass = False
    func = ""
    for line in sourceFile:
        line = line.strip()
        if isInclass and line.startswith("};"):
            break
        if isInclass:
            if line.startswith("virtual"):
                line = line.replace("\t", " ")
                ParseFuncAttrib(dom, root, line)
        elif line.startswith("class") and line.endswith("TraderSpi"):
            isInclass = True
    sourceFile.close()

def Parse(destFile, dataTypeFile, structFile, apiFile):
    impl = xml.dom.minidom.getDOMImplementation()
    dom = impl.createDocument(None, 'root', None)
    root = dom.documentElement
    typeNodes = dom.createElement('types')
    fieldNodes = dom.createElement('fields')
    spiNodes = dom.createElement('spi')
    types = {}
    ParseDataType(dom, typeNodes, dataTypeFile, types)
    ParseStruct(dom, fieldNodes, structFile, types)
    ParseSpiFunc(dom, spiNodes, apiFile)
    root.appendChild(typeNodes)
    root.appendChild(fieldNodes)
    root.appendChild(spiNodes)
    f = open(destFile, 'w')
    dom.writexml(f, indent="", addindent='\t', newl='\n', encoding="utf8")
    f.close()

def main():
    parseLists = ET.parse("ParseList.xml").getroot()
    for parseList in parseLists:
        destFile = parseList.get("destFile")
        dataTypeFile = parseList.get("dataTypeFile")
        structFile = parseList.get("structFile")
        apiFile = parseList.get("apiFile")
        print destFile, dataTypeFile, structFile, apiFile
        Parse(destFile, dataTypeFile, structFile, apiFile)

if __name__ == '__main__':
    main()
