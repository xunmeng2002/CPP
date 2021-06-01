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
    def __str__(self):
        return ("ID[%s] Name[%s] Desc[%s] Length[%s]" % (self.ID, self.Name, self.Desc, self.Length))

def get_macros(macroFile):
    dom = xml.dom.minidom.parse(macroFile)
    root = dom.documentElement
    macros = {}
    for node in root.getElementsByTagName("macro"):
        macro = Macro()
        macro.ID = node.getAttribute("id")
        macro.Name = node.getAttribute("name")
        macro.Desc = node.getAttribute("desc")
        if node.hasAttribute("length"):
            macro.Length = node.getAttribute("length")
        macros[macro.ID] = macro
    return macros
	
def CreatePbStepModel(destFile, schemaFile, macros):
    dom = xml.dom.minidom.parse(schemaFile)
    root = dom.documentElement
    fields = dom.getElementsByTagName("fields")[0]
    for field in fields.getElementsByTagName("field"):
        for item in field.getElementsByTagName("item"):
            macro = macros[item.getAttribute("id")]
            item.setAttribute("name", macro.Name)
            item.setAttribute("desc", macro.Desc)
            item.setAttribute("length", macro.Length)
    f = open(destFile, 'w')
    dom.writexml(f, indent="", addindent='', newl='', encoding="utf8")
    f.close()
	
if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: ParsePbStepModel.py destFile schema.xml macros.xml")
        exit(-1)
    destFile = sys.argv[1]
    schemaFile = sys.argv[2]
    macrosFile = sys.argv[3]
    macros = get_macros(macrosFile)
    CreatePbStepModel(destFile, schemaFile, macros)
