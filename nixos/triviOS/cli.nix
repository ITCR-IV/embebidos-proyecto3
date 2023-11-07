{ pkgs, ... }: {
  config = {
    environment.systemPackages = with pkgs; [
      libraspberrypi
      libgpiod
    ];

    users.users."root".initialPassword = "password";
  };
}
