{ pkgs ? import <nixpkgs> {}}:
let
  run = pkgs.writeShellScriptBin "run" ''
    #!/usr/bin/env bash
    mpic++ -o main main.cpp && mpiexec -n 3 ./main
  '';
in
pkgs.mkShell {
  buildInputs = [
    pkgs.mpi
    pkgs.gcc
    pkgs.bash

    run
  ];
}
