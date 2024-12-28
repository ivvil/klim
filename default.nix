{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    buildInputs = with pkgs; [
      platformio
      ccls
      # optional: needed as a programmer i.e. for esp32
      # pkgs.avrdude
    ];
    shellHook = ''
export PLATFORMIO_CORE_DIR=$PWD/.platformio
'';
}
