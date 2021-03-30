#!/bin/perl

print "please input a temperature (e.g., 32F, 100C)\n";

$input = <STDIN>;
chomp($input);

if ($input =~ m/^([-+]?[0-9]+)([CF])$/i)
{
    $InputNum = $1;
    $type = $2
}
#!/usr/bin/perl

# print "Enter a string data in Celsius:\n";
# $data = <STDIN>;
# chomp($data);

# $data = "Jeffs";

# if ($data =~ m/^[a-zA-Z]+$/i)
# {
#     print "$data is legal\n";
# }
# else
# {
#     print "illegal data\n";
# }

# if ($data =~ s/^[A-Z]+$/123/i)
# {
#     print "$data is legal\n";
# }
# else
# {
#     print "illegal data\n";
# }

# $data = "Jeffs";

# if ($data =~ s/(?<=\bJeff)(?=s\b)/'/g)
# {
#     print "$data is legal\n";
# }
# else
# {
#     print "illegal data\n";
# }


# $data = "Jeffs";

# if ($data =~ s/(?=s\b)(?<=\bJeff)/'/g)
# {
#     print "$data is legal\n";
# }
# else
# {
#     print "illegal data\n";
# }

# $text = "The population of 298444215 is growing";

# $text =~ s/(?<=\d)(?=(\d\d\d)+\b)/,/g;

# $text = "281421906";
# $text =~ s/(\d)((\d\d\d)+?)/$1,$3/g;

# $text = "

# ";

# $text =~ s/^\s$/<p>/g;

# print "$text";

$text = "abcde123AZ";

$text =~ s/([a-zA-Z0-9])*?(?![AZ])/$1/g;

print "$text"
