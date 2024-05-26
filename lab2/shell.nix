{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  shellHook = ''
    alias run="mpicxx main.cpp -o main && mpirun -np 3 ./main"
  '';
  buildInputs = [
    pkgs.mpi
  ];
}
