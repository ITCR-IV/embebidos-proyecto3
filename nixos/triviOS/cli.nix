{ pkgs, ... }: {
  config = {
    environment.systemPackages = with pkgs; [
      libraspberrypi
      libgpiod
      vim
      i2c-tools
      ht16k33
    ];

    users.users."root".initialPassword = "password";
  };
}
