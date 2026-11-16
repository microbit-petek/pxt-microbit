{
  description = "Dev environment for pxt-microbit";

  inputs = {
    nixpkgs.url = "github:NixOs/nixpkgs/nixos-26.05";
  };

  outputs =
    { self, nixpkgs }:
    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      forEachSupportedSystem =
        f:
        nixpkgs.lib.genAttrs supportedSystems (
          system:
          f {
            pkgs = import nixpkgs { inherit system; };
          }
        );
    in
    {
      devShells = forEachSupportedSystem (
        { pkgs }: {
          default = pkgs.mkShell {
            packages = [
              # Build toolchain
              pkgs.nodejs
              pkgs.git
              pkgs.python3
              pkgs.cmake
              pkgs.gcc-arm-embedded-13

              # Python packages
              pkgs.python313Packages.distutils
            ];

            shellHook = /* bash */ ''
              export NPM_CONFIG_PREFIX="$PWD/.npm-global"
              export PATH="$NPM_CONFIG_PREFIX/bin:$PATH"
              export PUPPETEER_SKIP_DOWNLOAD=1
              export CMAKE_POLICY_VERSION_MINIMUM=3.5
              export PXT_NODOCKER=1
              export PXT_RUNTIME_DEV=1

              mkdir -p "$NPM_CONFIG_PREFIX"/{bin,lib}
            '';
          };
        }
      );
    };
}
