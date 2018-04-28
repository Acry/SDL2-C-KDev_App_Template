This is a C-SDL-GNU Make Template for [KDevelop](https://www.kdevelop.org/)

You can apply your changes and simply invoke `make` to create the template.  

`make install`  
will try to install the template.  
Think you may need to restart Kdev in order to recognize the template.  

It looks like the templates need to be in bzip format. I haven't found clean instruction to make templates at all.

compressed archive needs to be copied to:  
`/home/$USER/.local/share/kdevappwizard/templates`

templates coming with your distribution  are usually found in:
`/usr/share/kdevappwizard/templates`

In case you want to compile the code use:  
`make -f Makefile_program`  

Thanks to the Kdev and SDL Team!

[Link to this repository.](https://github.com/Acry/SDL2-C-KDev_App_Template)

[Get in touch on SDL-Discourse](https://discourse.libsdl.org/u/Acry/summary)
