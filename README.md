# node-grt library

A very approachable node native extension.

This repository serves as a nearly minimal native extension built on [Nan](https://github.com/nodejs/nan) with enough tooling to also make it a great starting point for more complex projects.

## Building

To compile the extension for the first time, run 

```
$ npm i
$ npm run configure
$ npm run build
```

All subsequent builds only need `npm run build`