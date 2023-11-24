{ config, modulesPath, pkgs, ... }:

{
  imports = [
    (modulesPath + "/installer/sd-card/sd-image.nix")
  ];

  disabledModules = [
    (modulesPath + "/profiles/base.nix")
    (modulesPath + "/profiles/all-hardware.nix")
  ];

  config = {
    sdImage = {
      firmwareSize = 30;
      populateFirmwareCommands =
        let
          configTxt = pkgs.writeText "config.txt"
            ''
              [pi3]
              kernel=u-boot-rpi3.bin

              [cm4]
              # Enable host mode on the 2711 built-in XHCI USB controller.
              # This line should be removed if the legacy DWC2 controller is required
              # (e.g. for USB device mode) or if USB support is not required.
              otg_mode=1

              [all]
              # Boot in 64-bit mode.
              arm_64bit=1

              # U-Boot needs this to work, regardless of whether UART is actually used or not.
              # Look in arch/arm/mach-bcm283x/Kconfig in the U-Boot tree to see if this is still
              # a requirement in the future.
              enable_uart=1

              # Prevent the firmware from smashing the framebuffer setup done by the mainline kernel
              # when attempting to show low-voltage or overtemperature warnings.
              avoid_warnings=1

              dtparam=i2c_arm=on
            '';
        in
        ''
          (cd ${pkgs.raspberrypifw}/share/raspberrypi/boot && cp bootcode.bin fixup*.dat start*.elf $NIX_BUILD_TOP/firmware/)

          # Add the config
          cp ${configTxt} firmware/config.txt

          # Add pi3 specific files
          cp ${pkgs.ubootRaspberryPi3_64bit}/u-boot.bin firmware/u-boot-rpi3.bin

          # Add dtbs
          cp ${pkgs.raspberrypifw}/share/raspberrypi/boot/*.dtb firmware/
          cp -r ${pkgs.raspberrypifw}/share/raspberrypi/boot/overlays firmware/
        '';
      populateRootCommands = ''
        mkdir -p ./files/boot
        ${config.boot.loader.generic-extlinux-compatible.populateCmd} -c ${config.system.build.toplevel} -d ./files/boot
      '';
    };

    boot = {
      initrd.includeDefaultModules = false;

      initrd.kernelModules = [ "bcm2835_dma" "i2c_bcm2835" ];

      kernelModules = [ "i2c_bcm2835" "i2c_dev" ];

      kernelPackages = pkgs.linuxPackagesFor (pkgs.linux_rpi3.overrideDerivation (super: {
        buildFlags = super.buildFlags ++ [
          "KBUILD_BUILD_VERSION=1-${config.system.nixos.distroName}"
        ];
      }));

      # The serial ports listed here are:
      # - ttyS0: for Tegra (Jetson TX1)
      # - ttyAMA0: for QEMU's -machine virt
      # - ttyS1: mini UART
      kernelParams = [
        "console=ttyS0,115200n8"
        "console=ttyAMA0,115200n8"
        "console=tty0"
        "console=ttyS1,115200n8"
        "cma=256M"
      ];

      loader.grub.enable = false;
      loader.generic-extlinux-compatible.enable = true;

      consoleLogLevel = pkgs.lib.mkDefault 7;

    };

    hardware = {
      enableRedistributableFirmware = true;
      i2c.enable = true;
      deviceTree.overlays = [{
        name = "i2c1-overlay";
        dtsText = ''
          /dts-v1/;
          /plugin/;

          / {
                  compatible = "brcm,bcm2837";

                  fragment@0 {
                         target = <&i2c1>;

                          __overlay__ {
                                  status = "okay";
                          };
                  };


              };
        '';
      }];
    };
  };
}
