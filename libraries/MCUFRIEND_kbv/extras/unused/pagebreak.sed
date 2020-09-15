# skip the Ilitek PDF page footers.
/^a-.*/,/^Page.*/d
# skip the GalaxyCore PDF page headers.
/^Page*/,/^132RGB.*/d
# GalaxyCore //comment// to //comment
s/----\/\/$/----/
# skip the Himax PDF page footers.
/^Him.ax Confidential*/,/^APPLICATION NOTE/d
/^-P.*Himax Confidential*/,/^APPLICATION NOTE/d
# skip the Renesas PDF page footers.
/^[0-9]+$/,/Renesas SP Drivers/d
#/Initial Code(/d
# comment the Panel Title
s/^[1-9]/\/\/ &/
# remove Enter/Exit Sleep functions
/^[Vv]oid.*Sleep/,/^}/d
/^[Vv]oid.*Standby/,/^}/d
# legal function name
/^void/s/[.]//
# remove hardware Reset sequence
/Reset LCD Driver/,/Start Initial Sequence/d
