{ pkgs, ... }: {
  config = {
    environment.systemPackages = with pkgs; [
      libraspberrypi
      libgpiod
			vim
    ];

    users.users."root".initialPassword = "password";
  };
}
