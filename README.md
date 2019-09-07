# Reason Remote Data

This is project is based on the great gist [https://gist.github.com/idkjs/8e723a86f09843c4038123c45c846f75](remotedata) module.
It's just trying to go through the steps of releasing a library.

Use this if you actual need `remotedata`: [remotedata-re](https://github.com/lrosa007/remotedata-re)

## Setup

Install the module:

```bash
yarn add @aa/reason-remote-data
```

Then add it to your `bsconfig.json`:

```json
{
  "bs-dependencies": ["reason-react", "@aa/reason-remote-data"]
}
```

## Publishing

```bash
npm publish
```

You will have to work your way through the `npm publish` failures to get it to go. At first, I named the project `@aa/reason-remote-data` which wasnt accepted. I guess it already in use or reserved on `npm`. After the change it worked.

## Usage

TODO
