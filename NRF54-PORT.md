# nRF54L15 port

Currently the L15 port will only build locally, as the cloud servers have no notion of how to build for it.

## How to generate a hex for the L15
### Using nix devshell
#### Set up the environment
The flake provides all the tooling and environment variables needed to build this project.
If you have nix installed, run `nix develop` to enter the shell.
The first time you do this it will take a little while to collect the packages and set up the environment.
To exit the shell, use Ctrl-D or type `exit`.

Optionally, you can install direnv and nix-direnv, which will automatically enter and leave the devshell as you navigate in and out of the repo directory.
To use this, run
```sh
echo "use flake" > .envrc
direnv allow
```

#### Set up pxt-microbit
Run
```sh
npm install -g pxt
npm install
```

#### Build the runtime
The v3 runtime hex is built and cached with `pxt buildtarget --local`.


### Without the devshell
#### Set up the environment
Clone `pxt-microbit` and follow the instructions for local server setup in the [README](README.md).

**Note:** before running `npm install` you may want to run `export PUPPETEER_SKIP_DOWNLOAD=1` to save time.

To build the hex you will also need:
- Python3 with distutils
- CMake >= 3.24
- Arm GCC 13

#### Configure git for private repo access
All relevant repos are currently private, and so can't be accessed on github via https.
Exporting the following variables will override the https clone with ssh instead:
```sh
export GIT_CONFIG_COUNT=1
export GIT_CONFIG_KEY_0='url.git@github.com:microbit-foundation/.insteadOf'
export GIT_CONFIG_VALUE_0='https://github.com/microbit-foundation/'
```

#### Build the runtime
The v3 runtime hex is built and cached with
```sh
PXT_NODOCKER=1 \
PXT_COMPILE_SWITCHES="csv-mbcodal3" \
CMAKE_POLICY_VERSION_MINIMUM=3.5 \
pxt buildtarget --local
```

### Serve the site and open in the browser
The site is served with the local cache using `pxt serve --local`.
When opening the site in the browser, a flag is required to tell the site to only use the v3 runtime, as opposed to creating a universal hex. The URL is
```http://localhost:3232/index.html#?compile=csv-mbcodal3```

You can now create a MakeCode project in the usual way.
Choose "Download as File".

## Flashing the nRF54L15DK board
### Using JLinkExe cli tool
The JLinkExe cli tool comes as part of the [J-Link Software and Documentation Pack](https://www.segger.com/downloads/jlink/).
It is included in the devshell tooling.
Run
```
  JLinkExe -device nRF54L15_M33 -if SWD -speed 4000 -autoconnect 1
```
Then from within the tool, run the following:
```
  LoadFile path/to/microbit-project.hex
  r
  g
```

### Alternatives
Nordic supply the [nRF Connect](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-Desktop) suite which provides a drag-and-drop programming tool.  

## Development setup
- For development, clone the [codal-microbit-v3](https://github.com/microbit-foundation/codal-microbit-v3) repo.
Check the `mbcodal3` entry in `pxtarget.json` for the correct branch to check out.
- Make sure you've run `pxt buildtarget --local` (see [Build the runtime](#build-the-runtime) above) at least once so that the various projects' `built` folders are populated.
- Navigate to `libs/blocksprj/built/codal/libraries/` and run the following
```
  rm -rf codal-microbit-v3
  ln -s /path/to/local/codal-microbit-v3 codal-microbit-v3
```

Currently `blocksprj` is the only template which needs modifying in this way, as all built templates are only dependent on `core`.
When `radio` and `microphone` are reinstated, this will no longer be the case, and symlinks will have to be introduced in all templates which contain a `built` folder.

If not using the nix devshell, when [building the runtime](#build-the-runtime-1) add `PXT_RUNTIME_DEV=1` to help pick up changes to the CODAL libraries and trigger rebuilds.
The nix devshell includes this variable automatically.

Whichever setup you use, you will also need to delete `built/hexcache/<sha>.hex` otherwise the rebuild will be skipped.

**Note:** The `--force` switch for pxt will redo everything, including pulling libraries, which will wipe out the symlink.
