{
  config = {
    networking = {
      hostName = "tripi";
      firewall.allowedTCPPorts = [ 80 ];

      wireless = {
        enable = true;
        environmentFile = "/var/lib/wlan.conf";
        networks."@WLAN_SSID@".psk = "@WLAN_PSK@";
      };
    };

    services.openssh = {
      enable = true;
      settings.PasswordAuthentication = true;
      settings.PermitRootLogin = "yes";
    };
  };
}
