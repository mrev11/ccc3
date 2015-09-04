

#define  GTK_POS_LEFT       0
#define  GTK_POS_RIGHT      1
#define  GTK_POS_TOP        2
#define  GTK_POS_BOTTOM     3


function main()

local window
local notebook
local i,frame
    
    gtk.init ()
       
    window:=gtkwindowNew()
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_size_request(600,500)
    window:set_title("Tabbed Window")
    window:set_border_width(20)

    notebook:=gtknotebookNew()  //ez a tabbed pane!
    window:add(notebook)
    notebook:set_tab_pos(GTK_POS_TOP ) //fulek fenn

    for i:=1 to 4
        frame:=gtkframeNew("Append Frame "+str(i)::alltrim)
        frame:set_border_width(10)
        frame:set_size_request(100,90)
        frame:add( gtklabelNew("APPEND FRAME "+str(i)::alltrim) )
        notebook:append_page(frame, gtklabelNew("Page "+str(i)::alltrim))
    next

    notebook:append_page(gtkcalendarNew(),gtk.label.new("Calendar"))

    window:show_all
    gtk.main()


