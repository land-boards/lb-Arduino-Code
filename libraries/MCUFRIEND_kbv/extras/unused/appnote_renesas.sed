#n  does not work.  use nsed -n

######################################################################
# parse Renesas App Note sequence. e.g.
# {setc, [107], W, 0x000B0}
# {setc, 0x000D0}
# {setp, 0x00033}
# {time, 0040,ms}

:Renesas
# //Title line
s/^[1-9].*/\/\/ &/
# //comment to /* comment */
s/[/][/]\(.*\)/\/\*\1\*\/ /
/{setc,/b good
/{time,/b good
b print
{
:good
   h
   :args
   n
   s/[/][/]\(.*\)/\/\*\1\*\/ /
   # append any data to Hold space
   /setp/{
      H 
      b args
   }
#   /^$/b args
   x
   # verbose format
   s/, \[[0-9]+\], W, 0x/, 0x/g
   # parse command byte to (0xNN),
   s/{setc, 0x000\(..\)}/    (0x\1), /
   # parse data byte to 0xNN,
   #   s/\nLCD_ILI9486_INDEX(//g
   s/\n{setp, 0x000\(..\)}/0x\1, /g
   s/\n{setp, 0x00\(...\)}/0x\1, /g
   # parse delay times
   s/{time, 0*\(.*\),ms}/    TFTLCD_DELAY8, \1, /
   s/)\;/,/g
   p
   x
   b Renesas
}
:print
p
