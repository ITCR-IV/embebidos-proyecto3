{ pkgs, ... }: {
  config = {

    systemd.services.ImageServer = {
      enable = true;
      description = "ImageServer";

      after = [ "network.target" "network-online.target" "nss-lookup.target" ];
      requires = [ "network.target" ];
      wants = [ "network-online.target" ];

      serviceConfig = {
        ExecStart = "${pkgs.ImageServer}/bin/ImageServer";
        Type = "simple";
        Restart = "always";
      };
      wantedBy = [ "multi-user.target" ];
    };

    # TODO: Poner nuestros propios servicios web
    # nginx = {
    #   enable = true;

    #   recommendedGzipSettings = true;
    #   recommendedOptimisation = true;
    #   recommendedProxySettings = true;

    #   virtualHosts.home-manager = {
    #     default = true;

    #     locations = {
    #       "/static/".alias = "/run/nginx/static/";

    #       "/".extraConfig = ''
    #         uwsgi_pass unix://${config.services.uwsgi.runDir}/uwsgi.sock;
    #       '';
    #     };
    #   };
    # };

    # uwsgi = {
    #   enable = true;

    #   user = "nginx";
    #   plugins = [ "python3" ];

    #   instance = {
    #     type = "normal";
    #     pythonPackages = py: [ (py.callPackage ../ui { }) ];

    #     module = "homemanager.wsgi";
    #     socket = "${config.services.uwsgi.runDir}/uwsgi.sock";
    #   };
    # };

    services.udev.extraRules = ''
      KERNEL=="gpiochip*", GROUP="uwsgi", MODE="660"
      KERNEL=="video*", GROUP="uwsgi", MODE="660"
    '';
  };
}
