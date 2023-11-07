{ config, pkgs, ... }: {
  config.services = {
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

    udev.extraRules = ''
      KERNEL=="gpiochip*", GROUP="uwsgi", MODE="660"
      KERNEL=="video*", GROUP="uwsgi", MODE="660"
    '';
  };
}
