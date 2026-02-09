{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  packages = with pkgs; [
    xorg.libX11
    xorg.libXext
    xorg.libXrandr
    xorg.libXcursor
    xorg.libXi
    xorg.libXxf86vm
    xorg.libXinerama
    xorg.xorgproto

    libGL.dev
  ];
}
