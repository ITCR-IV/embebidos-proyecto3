{ config, modulesPath, pkgs, ... }: {
  imports = [
    (modulesPath + "/installer/sd-card/sd-image-aarch64.nix")
  ];

  disabledModules = [
    (modulesPath + "/profiles/base.nix")
    (modulesPath + "/profiles/all-hardware.nix")
  ];

  config = {
    boot = {
      initrd.includeDefaultModules = false;

      kernelPackages = pkgs.linuxPackagesFor (pkgs.linux_rpi3.overrideDerivation (super: {
        buildFlags = super.buildFlags ++ [
          "KBUILD_BUILD_VERSION=1-${config.system.nixos.distroName}"
        ];
      }));

      kernelParams = [
        "console=ttyS1,115200n8"
        "cma=256M"
      ];
    };

    hardware.enableRedistributableFirmware = true;
  };
}
