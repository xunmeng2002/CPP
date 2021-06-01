#!python2
#!coding:utf-8

import xml.dom.minidom

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
        type = ""
        basetype = ""
        name = ""
        custom = "False"
        if item.startswith("CThostFtdc"):
            attributes = item.split("*")
            type = attributes[0].strip()
            basetype = ""
            name = type[10 : type.rfind("Field")]
            custom = "True"
        elif item.startswith("THOST_TE"):
            attributes = item.split(" ")
            type = attributes[0].strip()
            basetype = "enum"
            name = attributes[1].strip()
        elif item.startswith("char *") or item.startswith("const char *") :
            type = item[0 : item.find("*")+1]
            basetype = "string"
            name = item[item.find("*")+1:]
        else:
            attributes = item.split(" ")
            type = attributes[0]
            basetype = type
            name = attributes[1]

        param = dom.createElement('param')
        param.setAttribute("type", type)
        param.setAttribute("basetype", basetype)
        param.setAttribute("name", name)
        param.setAttribute("custom", custom)
        func.appendChild(param)

def ParseFuncAttrib(dom, root, line): 
    func = dom.createElement('func')
    if line.startswith("virtual const char *"):
        func.setAttribute("return", "const char *")
        func.setAttribute("name", line[line.find("*")+1 : line.find("(")])
    else:
        items = line.split(" ")
        func.setAttribute("return", items[1])
        func.setAttribute("name", items[2][0 : items[2].find("(")])
    ParseFuncParams(dom, func, line)
    root.appendChild(func)

def ParseApiFunc(dom, root, filename):
    sourceFile = open(filename, "r")
    isInclass = False
    func = ""
    for line in sourceFile:
        line = line.strip()
        if isInclass and line.startswith("};"):
            break
        elif line.startswith("class") and line.endswith("TraderApi"):
            isInclass = True
        if isInclass:
            if line.startswith("virtual"):
                line = line.replace("\t", " ")
                ParseFuncAttrib(dom, root, line)
    sourceFile.close()

def ParseSpiFunc(dom, root, filename):
    sourceFile = open(filename, "r")
    isInclass = False
    func = ""
    for line in sourceFile:
        line = line.strip()
        if isInclass and line.startswith("};"):
            break
        elif line.startswith("class") and line.endswith("TraderSpi"):
            isInclass = True
        if isInclass:
            if line.startswith("virtual"):
                line = line.replace("\t", " ")
                ParseFuncAttrib(dom, root, line)
    sourceFile.close()

def Parse(destFile, dataTypeFile, structFile, apiFile, apiVersion):
    impl = xml.dom.minidom.getDOMImplementation()
    dom = impl.createDocument(None, 'root', None)
    root = dom.documentElement
    root.setAttribute("apiversion", apiVersion)
    typeNodes = dom.createElement('types')
    fieldNodes = dom.createElement('fields')
    apiNodes = dom.createElement('api')
    spiNodes = dom.createElement('spi')
    types = {}
    ParseDataType(dom, typeNodes, dataTypeFile, types)
    ParseStruct(dom, fieldNodes, structFile, types)
    ParseApiFunc(dom, apiNodes, apiFile)
    ParseSpiFunc(dom, spiNodes, apiFile)
    root.appendChild(typeNodes)
    root.appendChild(fieldNodes)
    root.appendChild(apiNodes)
    root.appendChild(spiNodes)
    f = open(destFile, 'w')
    dom.writexml(f, indent="", addindent='\t', newl='\n', encoding="utf8")
    f.close()

def main():
    apiPath = "./"
    dataTypeFile="/include/ThostFtdcUserApiDataType.h"
    structFile="/include/ThostFtdcUserApiStruct.h"
    apiFile="/include/ThostFtdcTraderApi.h"
    apiVersions = ["6.3.15", "6.5.1"]
    for apiVersion in apiVersions:
        fullDestFile = apiPath + "CtpApiModel_" + apiVersion + ".xml"
        fullDataTypeFile = apiPath + apiVersion + dataTypeFile
        fullStructFile = apiPath + apiVersion + structFile
        fullApiFile = apiPath + apiVersion + apiFile
        print fullDestFile, fullDataTypeFile, fullStructFile, fullApiFile
        Parse(fullDestFile, fullDataTypeFile, fullStructFile, fullApiFile, apiVersion)

if __name__ == '__main__':
    main()
