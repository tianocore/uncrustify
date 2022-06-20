/* Processor information */
STATIC SMBIOS_TYPE4  mSmbiosType4 = {
  {
    SocketTypeBase,                                           // Socket type
    ProcessorVersionBase,                                     // Processor version, update dynamically
    (                                                         // Status
                                                   (1 << 6) | // CPU Socket Populated
                                                   (1 << 0)   // CPU Enabled
    ),
    ProcessorUpgradeOther,                                    // Processor Upgrade
    (                                                         // Processor characteristics
                                                   (1 << 2) | // 64-bit Capable
                                                   (1 << 3) | // Multi-Core
                                                   (1 << 5) | // Execute Protection
                                                   (1 << 6) | // Enhanced Virtualization
                                                   (1 << 7)   // Power/Performance Control
    ),
    ProcessorFamily       // Processor Family
  },
  TYPE4_STRINGS
};
