function [ output_args ] = analyse( infile, outfile )
%ANALYSE Summary of this function goes here
%   Detailed explanation goes here
in = audioread(infile);
out = audioread(outfile);

H = spectrum.welch;
figure
psd(H, in, 'Fs', 8000);
figure
psd(H, out, 'Fs', 8000);
figure
plot(in(1:1000));
figure
plot(out(1:1000));
end

