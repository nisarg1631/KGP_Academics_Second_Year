r = 1000;
c = 0.000000100;
x = [1:1:100000];
y = 20*log10(1./sqrt(1+(power(r*c*x*2*pi,2))));
x1=[50, 150, 450, 1300, 3800, 6500, 11500, 25000];
y1=[-0.003, -0.038, -0.335, -2.221, -8.268, -12.505, -17.355, -24.408];
semilogx(x,y,x1,y1,'o','MarkerFaceColor',[0.741 0.447 0])
str = {'R = 1 k\Omega','C = 100 nF'};
annotation('textbox','String',str,'FitBoxToText','on');
legend('Theoretical', 'Observed')
xlabel('Frequency (Hz)')
ylabel('Magnitude (dB)')
title('Frequency Response of Low Pass RC Filter')
grid on