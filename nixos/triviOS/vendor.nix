{
  config = {
    system = {
      nixos = {
        distroId = "trivios";
        distroName = "TriviOS";
        variant_id = "rpi3";
      };

      stateVersion = "23.05";
    };

    sdImage.imageBaseName = "trivios-sd-image";
  };
}
