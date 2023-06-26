import sys

USA_OFFSETS = [
    (0x806599A0, -0x5700)  # After ErrorMessageArchive
]

JPN_OFFSETS = [
    (0x806599A0, -0x5F20),  # After ErrorMessageArchive
    (0x8072DD80, -0x5F40)  # BSS Start
]

TWN_OFFSETS = [
    # .text
    (0x8047B110, 0x10),  # initTextBoxPane__14LayoutCoreUtilFPQ34nw4r3lyt7TextBoxPCcUl
    (0x80492340, 0x50),  # appear__9StaffRollFv
    (0x80494AA0, 0x70),
    (0x804BD390, 0x90),  # getLanguageNum__2MRFv
    (0x8054B440, 0x100),
    (0x805E7BE0, 0x110),  # wpad.a
    (0x805E8140, 0x120),  # wpad.a
    (0x805E8DF0, 0x1B0),  # wpad.a
    (0x805EA130, 0x1D0),  # WPADStartFastSimpleSync
    (0x805EA390, 0x300),
    (0x805EAC60, 0x480),
    (0x805F08C0, 0x490),
    (0x805F0FD0, 0x4A0),
    (0x805F3B00, 0x4C0),
    (0x805F43D0, 0x4E0),
    (0x805F46A0, 0x4F0),
    (0x805F6DC0, 0x570),
    # .ctors, also applies to .dtors and .rodata
    (0x80643D20, 0x580),
    # .rodata
    (0x8064CBB0, 0x590),  # After language-related table
    (0x8064CF18, 0x598),  # cLanguages__22@unnamed@Language_cpp@
    (0x8064CF80, 0x5A0),
    (0x806599A0, -0x5460),  # After ErrorMessageArchive
    # .data
    (0x806F920C, -0x5464),  # "TxtGalaxyNameU"
    (0x806F9220, -0x5468),  # "Unknown"
    (0x80700E18, -0x5458),  # "English"
    (0x80700F00, -0x5460),
    (0x807024B0, -0x5448),  # "/ObjectData/Yoshi.arc"
    (0x8070260C, -0x5468),  # "/ObjectData/PlanetMapDataTable.arc"
    (0x80702758, -0x5448),  # "/LayoutData/GameOver.arc"
    (0x8070C560, -0x5440),
    (0x8070CB58, -0x5438),
    (0x80721960, -0x5440),
    (0x807255C4, -0x5434),
    (0x807255C4, -0x543C),
    (0x807258D8, -0x5430),
    # .bss
    (0x8072DD80, 0xEA40),
    # .sdata
    (0x807D4A20, -0xAC100),
    (0x807D59B8, -0xAC0F8),
    (0x807D59D8, -0xAC0F0),
    (0x807D5DEC, -0xAC0E8),
    # .sbss
    (0x807D6480, -0xAC100),
    (0x807DBA48, -0xAC0F8),
    (0x807DBFE0, -0xAC0E0),
    (0x807DC1F4, -0xAC0DC),
    (0x807DC210, -0xAC0D8),
    (0x807DC3A0, -0xAC0E0),
    # .sdata2
    (0x807E7880, -0xAC0D0),
    # .sbss2
    (0x807E86C0, -0xAC0E0),
]

KOR_OFFSETS = [
    # .text
    (0x8047B110, 0x10),  # initTextBoxPane__14LayoutCoreUtilFPQ34nw4r3lyt7TextBoxPCcUl
    (0x80492340, 0x50),  # appear__9StaffRollFv
    (0x80494AA0, 0x70),
    (0x804BD390, 0x90),  # getLanguageNum__2MRFv
    (0x8054B440, 0x100),
    (0x805E7BE0, 0x110),  # wpad.a
    (0x805E8140, 0x120),  # wpad.a
    (0x805E8DF0, 0x1B0),  # wpad.a
    (0x805EA130, 0x1D0),  # WPADStartFastSimpleSync
    (0x805EA390, 0x300),
    (0x805EAC60, 0x480),
    (0x805F08C0, 0x490),
    (0x805F0FD0, 0x4A0),
    (0x805F3B00, 0x4C0),
    (0x805F43D0, 0x4E0),
    (0x805F46A0, 0x4F0),
    (0x805F6DC0, 0x570),
    # .ctors, also applies to .dtors and .rodata
    (0x80643D20, 0x580),
    # .rodata
    (0x8064CBB0, 0x590),  # After language-related table
    (0x8064CF18, 0x598),  # cLanguages__22@unnamed@Language_cpp@
    (0x8064CF80, 0x5A0),
    (0x806599A0, -0x68C0),  # After ErrorMessageArchive
    # .data
    (0x806F920C, -0x5464),  # "TxtGalaxyNameU"
    (0x806F9220, -0x5468),  # "Unknown"
    (0x80700E18, -0x5458),  # "English"
    (0x80700F00, -0x5460),
    (0x807024B0, -0x5448),  # "/ObjectData/Yoshi.arc"
    (0x8070260C, -0x5468),  # "/ObjectData/PlanetMapDataTable.arc"
    (0x80702758, -0x5448),  # "/LayoutData/GameOver.arc"
    # .data
    (0x806F920C, -0x68C4),  # "TxtGalaxyNameU"
    (0x806F9220, -0x68C8),  # "Unknown"
    (0x80700E18, -0x68B8),  # "English"
    (0x80700F00, -0x68C0),
    (0x807024B0, -0x68A8),  # "/ObjectData/Yoshi.arc"
    (0x8070260C, -0x68C8),  # "/ObjectData/PlanetMapDataTable.arc"
    (0x80702758, -0x68A8),  # "/LayoutData/GameOver.arc"
    (0x8070C560, -0x68A0),
    (0x8070CB58, -0x6898),
    (0x80721960, -0x68A0),
    (0x807255C4, -0x6894),
    (0x807255C4, -0x689C),
    (0x807258D8, -0x6890),
    # .bss
    (0x8072DD80, 0xD600),
    # .sdata
    (0x807D4A20, -0xAD560),
    (0x807D59B8, -0xAD558),
    (0x807D59D8, -0xAD550),
    (0x807D5DEC, -0xAD548),
    # .sbss
    (0x807D6480, -0xAD560),
    (0x807DBA48, -0xAD558),
    (0x807DBFE0, -0xAD540),
    (0x807DC1F4, -0xAD53C),
    (0x807DC210, -0xAD538),
    (0x807DC3A0, -0xAD540),
    # .sdata2
    (0x807E7880, -0xAD530),
    # .sbss2
    (0x807E86C0, -0xAD540),
]

OFFSETS = {
    "JPN": JPN_OFFSETS,
    "USA": USA_OFFSETS,
    "KOR": KOR_OFFSETS,
    "TWN": TWN_OFFSETS
}

for offsets in OFFSETS.values():
    offsets.sort(key=lambda t: t[0], reverse=True)


def resolve_address(desired_address: int, region: str):
    if region == "PAL":
        return desired_address

    offset_info = OFFSETS[region]

    for address, offset in offset_info:
        if desired_address >= address:
            return desired_address + offset

    return desired_address


if __name__ == '__main__':
    if len(sys.argv) >= 2:
        raw = sys.argv[1].removeprefix("0x")
        address = int(raw, 16)
        print(f" USA: 0x{resolve_address(address, 'USA'):08X}")
        print(f" JPN: 0x{resolve_address(address, 'JPN'):08X}")
        print(f" TWN: 0x{resolve_address(address, 'TWN'):08X}")
        print(f" KOR: 0x{resolve_address(address, 'KOR'):08X}")
