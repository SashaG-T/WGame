# About
Basis for c-base wasm game engine!

# Setup
What you will need:
  - emsdk (duh!)
  - pscp (if you want to run 'make publish')
  - some version of 'make' to compile (I use 'mingw32-make' but you-do-you, okay?)
  - know how to setup a emsdk terminal (I've included a useful tool `env.bat` but you'll need to do some Environment Variable magic..)

You will have to replace the following Makefile variables with your own:
  - DOMAIN (example.com)
  - USER (user) 
  - WEBROOT (/home/user/path/to/webroot) (Must have leading '/' and no trailing '/')
  - PUBDIR (myarcade/mygame) (Must have not leading '/' and no trailing '/')
  - PPK ("path/to/key.ppk") (Must be fully-qulaified path to a ppk file)

If you don't plan on publishing to a website then you can leave them blank.

## env.bat
On my system I use a Environment Variable to point a directory that contains all my SDKS.
This Environment Variable is un-oddly called SDKS.

I do this so I can access an SDK such as emsdk using `%SDKS%/emsdk`.
It also helps keep project files the same across devices.

`env.bat` uses an Environment Variable called SDKS to setup the command prompt for usage with the emsdk.
You could setup the command prompt however you need too. `emsdk` provides utilities to setup a command prompt
too if you fancy that better. `env.bat` just allows me to work entirely within the workspace folder.

# Compile
`
  //setup our enviroment for emsdk!
  env.bat   //You'll need to add %SDKS% to your Environment Variables to use this bad boy

  //Alternative to env.bat
  // ./path/to/emsdk/emsdk_env.bat 

  //Clean if needed
  mingw32-make clean

  //Compile!
  mingw32-make

  //Publish to site!
  mingw32-make publish
`
# Testing
To test you must have a working HTTP server. You can set one up quickly using `http-server`.
Install `http-server` using `npm install -g http-server` (or you can publish to a site).
Just know that if you do use `http-server` that you'll need `node.js` installed and you must run
`http-server` in the folder where `index.html` is generated.

Remeber you clear your cache after each re-compile of the project too! Your browser will load the
old content and not the fresh re-complied version so just be wary of that.

# Publishing Notes
You must have a PPK file and the proper user privileges to publish directly to a site.
The make file variables are used in the following way with pscp to copy to webroot.
  - `pscp -r -i $(PPK) "wbin/$(firstword $(subst /, ,$(PUBDIR)))" "$(USER)@$(DOMAIN):$(WEBROOT)/"`

EXAMPLE:
  - `pscp -r -i "C:\path\to\cert.ppk" "wbin/arcade" "doug@dougsgames.com:/home/doug/path/to/webroot/"`
The below generates the above call to pscp.
  - `DOMAIN = dougsgames.com`
  - `USER = doug`
  - `WEBROOT = /home/doug/path/to/webroot`
  - `PUBDIR = myarcade/mygame`
  - `PPK = "C:\path\to\cert.ppk"`

## Publishing Manually
If you do not have access to a ppk or would rather publich manually so can by simply copying the contents of
the folder `wbin` to where ever you want.