r = 1000;
l = 0.500;
x = [1:1:100000];
y = 20*log10((2*pi*x*l)./sqrt((r*r)+(power(l*x*2*pi,2))));
x1=[50, 150, 450, 1300, 3800, 6500, 11500, 25000];
y1=[-16.182, -7.408, -1.762, -0.252, -0.030, -0.010, -0.003, -0.002];
semilogx(x,y,x1,y1,'o','MarkerFaceColor',[0.741 0.447 0])
str = {'R = 1 k\Omega','L = 500 mH'};
annotation('textbox','String',str,'FitBoxToText','on');
legend('Theoretical', 'Observed','location','northwest')
xlabel('Frequency (Hz)')
ylabel('Magnitude (dB)')
title('Frequency Response of High Pass RL Filter')
grid on