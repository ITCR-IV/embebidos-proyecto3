{
  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-23.05";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      crossSystem = "aarch64-linux";
      pkgs = import nixpkgs {
        inherit system;
        crossSystem = import ./triviOS/cross.nix;
        overlays = [ (import ./triviOS/overlay.nix) ];
      };
    in
    {
      formatter.${system} = pkgs.pkgsBuildBuild.nixpkgs-fmt;
      images = {
        pi3 = self.nixosConfigurations.triviOS.config.system.build.sdImage;
      };

      nixosConfigurations.triviOS = nixpkgs.lib.nixosSystem {
        inherit pkgs;
        system = crossSystem;
        modules = [ ./triviOS ];
      };

      packages.${crossSystem} = pkgs;
    };
}
