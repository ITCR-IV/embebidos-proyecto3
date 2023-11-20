{
  config = {
    networking = {
      hostName = "rpi3";
      firewall.allowedTCPPorts = [ 80 ];

      wireless = {
        enable = true;
        environmentFile = "/etc/wlan.conf";
        networks."@WLAN_SSID@".psk = "@WLAN_PSK@";
      };
    };

    # Por default conectar a cel de Ignacio
    environment.etc."wlan.conf".text = ''
            		WLAN_SSID=cascade
            		WLAN_PSK=12345678
      					'';

    services.openssh = {
      enable = true;
      settings.PasswordAuthentication = true;
      settings.PermitRootLogin = "yes";
    };
  };
}
