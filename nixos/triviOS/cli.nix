{ pkgs, ... }: {
  config = {
    environment.systemPackages = with pkgs; [
      libraspberrypi
      libgpiod
			vim
			i2c-tools
    ];

    users.users."root".initialPassword = "password";
  };
}
