#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import jtdom
from jtlib import jtutil


xml="""<proba>
    <szerencse>Öt szép szűzlány őrült írót nyúz</szerencse>
    <vanaki>
        <egyszer><![CDATA[ Forrón szereti! ]]></egyszer>
        <egyszer>Hopp</egyszer>
    </vanaki>
    <maskor>Kopp</maskor>
</proba>"""

node=jtdom.domparse(xml)

#jtutil.inspect(node,True)


def walk(node,text):
    """Összegyűjti a node alatti szővegeket."""

    if node.nodeValue==None:
        pass
    elif not isinstance(node.nodeValue,str):
        pass
    elif jtdom.wspace(node.nodeValue):
        pass
    else:
        text[0]+=node.nodeValue

    child=node.firstChild
    while child:
        walk(child,text)    
        child=child.nextSibling
    
   
    
    
text=[""]   
walk(node,text)
print(text)    


