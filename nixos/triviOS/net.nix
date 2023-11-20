{
  config = {
    networking = {
      hostName = "rpi3";
      firewall =
        {
          allowedTCPPorts = [ 80 ];
          allowedUDPPorts = [ 53 67 ]; # DNS & DHCP
        };


      interfaces.wlan0.ipv4.addresses = [
        {
          address = "192.168.1.1";
          prefixLength = 16;
        }
      ];

      wireless.enable = true;

      # wireless = {
      #   enable = true;
      #   environmentFile = "/etc/wlan.conf";
      #   networks."@WLAN_SSID@".psk = "@WLAN_PSK@";
      # };
    };

    services = {
      hostapd = {
        enable = true;
        interface = "wlan0";
        wpa = true;
        ssid = "triviOS";
        wpaPassphrase = "12345678";
      };

      dnsmasq = {
        enable = true;
        settings = {
          domain-needed = true;
          dhcp-range = [ "192.168.1.2,192.168.1.254" ];
        };
      };

      openssh = {
        enable = true;
        settings.PasswordAuthentication = true;
        settings.PermitRootLogin = "yes";
      };
    };
  };
}
