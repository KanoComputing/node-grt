# node-grt

🚨 Incomplete and unmaintained proof of concept. 🚨

An implementation of Nick Gillian's Gesture Recognition Toolkit ([GRT](https://github.com/nickgillian/grt)) in node.js

## Installation

This module is available on `npm`.

```
npm install --save node-grt
```

Prebuilt versions of the module are uploaded using the `prebuild` module. If your target platform doesn't have a prebuilt binary, npm will try to build the module.

## Building

To compile the extension for the first time, run 

```
$ npm i
$ npm run configure
$ npm run build
```

All subsequent builds only need `npm run build`

### Windows

Building on Windows requires the statically compiled grt library. As this file is over 100M, it is not versioned on this repository. The `.lib` file can be found here: [grt.lib](http://releases.kano.me/node-grt/win32/lib/grt.lib).

Place the `grt.lib` file in the `lib` folder of this module or update the `bindings.gyp` `libraries` section to specify the library's location. Then run the command specified in the Building section.
