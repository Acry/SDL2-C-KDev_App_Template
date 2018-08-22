KDev heavy Template
===================

This is a C-SDL-GNU Make Template for [KDevelop](https://www.kdevelop.org/)

[Simple DirectMedia Layer](https://www.libsdl.org/) is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D.  

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

**Useful links:**  
[Link to this repository.](https://github.com/Acry/SDL2-C-KDev_App_Template) | [SDL2-C-Tutorials](https://acry.github.io/) | [SDL2](https://www.libsdl.org/) | [SDL-Discourse](https://discourse.libsdl.org)  

**Contact**
[Get in touch on SDL-Discourse](https://discourse.libsdl.org/u/Acry/summary)