r = 1000;
l = 0.500;
x = [1:1:100000];
y = 20*log10(r./sqrt((r*r)+(power(l*x*2*pi,2))));
x1=[50, 150, 450, 1300, 3800, 6500, 11500, 25000];
y1=[-0.107, -0.871, -4.770, -12.476, -21.577, -26.232, -31.245, -38.416];
semilogx(x,y,x1,y1,'o','MarkerFaceColor',[0.741 0.447 0])
str = {'R = 1 k\Omega','L = 500 mH'};
annotation('textbox','String',str,'FitBoxToText','on');
legend('Theoretical', 'Observed')
xlabel('Frequency (Hz)')
ylabel('Magnitude (dB)')
title('Frequency Response of Low Pass RL Filter')
grid on