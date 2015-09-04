
#define  GTK_POS_LEFT       0
#define  GTK_POS_RIGHT      1
#define  GTK_POS_TOP        2
#define  GTK_POS_BOTTOM     3


function main()

local window
local table
local notebook
local i,frame,label,frm,lab
local calendar
    
    gtk.init ()
       
    window:=gtk.window.new() //; gtk.widget.show(window)
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.widget.set_size_request (window, 600, 500)
    gtk.window.set_title(window,"Tabbed Window")
    gtk.container.set_border_width(window,20)
    
    notebook:=gtk.notebook.new() //; gtk.widget.show(notebook)
    gtk.notebook.set_tab_pos(notebook,GTK_POS_TOP )

    table:=gtk.table.new(2,6,.t.) //; gtk.widget.show(table)
    gtk.table.attach(table,notebook,0,6,0,1) 
    //a szamok eloirjak, hova kerul a tartalom a table-n belul
    //a table kozbeiktatasa nelkul is mukodik a program
    //akkor az egesz window-t elfoglalja a notebook
    gtk.container.add(window,table)

    for i:=1 to 4
        frm:="Append Frame "+str(i)::alltrim
        lab:="Page "+str(i)::alltrim
        
        frame:=gtk.frame.new(frm) //; gtk.widget.show(frame)
        gtk.container.set_border_width(frame,10)
        gtk.widget.set_size_request(frame,100,90)
        
        label:=gtk.label.new(frm) //; gtk.widget.show(label)
        gtk.container.add(frame,label)
        
        label:=gtk.label.new(lab)
        gtk.notebook.append_page(notebook,frame,label)
    next
    
    calendar:=gtk.calendar.new() //; gtk.widget.show(calendar)
    gtk.notebook.append_page(notebook,calendar,gtk.label.new("Calendar"))

    gtk.widget.show_all(window)

    gtk.main()


