{ modulesPath, ... }: {
  imports = [
    (modulesPath + "/profiles/minimal.nix")
  ];

  config = {
    nix.enable = false;

    services.timesyncd.enable = false;

    systemd = {
      oomd.enable = false;
      coredump.enable = false;
    };
  };
}
