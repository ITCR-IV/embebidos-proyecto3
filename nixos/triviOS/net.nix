{
  config = {
    networking = {
      hostName = "rpi3";
      firewall =
        {
          allowedTCPPorts = [ 80 1717 ]; # SSH & ImageServer
          allowedUDPPorts = [ 53 67 ]; # DNS & DHCP
          extraCommands = ''
            iptables -P FORWARD ACCEPT
            iptables -F FORWARD
						iptables -t nat -A POSTROUTING -o enu1u1u1 -j MASQUERADE
          '';
        };


      interfaces.wlan0.ipv4.addresses = [
        {
          address = "192.168.1.1";
          prefixLength = 16;
        }
      ];

    };

    boot.kernel.sysctl = {
      "net.ipv4.ip_forward" = true;
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
        settings = {
          PasswordAuthentication = true;
          PermitRootLogin = "yes";
        };
      };
    };
  };
}
