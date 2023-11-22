self: super: {
  systemd = super.systemd.override {
    pname = "systemd-minimal";
    withAcl = false;
    withAnalyze = false;
    withApparmor = false;
    withAudit = false;
    withCompression = false;
    withCoredump = false;
    withCryptsetup = false;
    withDocumentation = false;
    withEfi = false;
    withFido2 = false;
    withHostnamed = false;
    withHomed = false;
    withImportd = false;
    withLibBPF = false;
    withLibidn2 = false;
    withLocaled = false;
    withMachined = false;
    withNetworkd = false;
    withNss = false;
    withOomd = false;
    withPCRE2 = false;
    withPolkit = false;
    withPortabled = false;
    withRemote = false;
    withResolved = false;
    withShellCompletions = false;
    withTimedated = false;
    withTimesyncd = false;
    withTpm2Tss = false;
    withUserDb = false;

    # Se implican y son necesarios:
    # withPam = true;
    # withHwdb = true;
    # withLogind = true;
  };

  libaom = super.libaom.override {
    enableButteraugli = false;
  };

  ht16k33 = self.callPackage ../../driver_ht16k33 { };
}
