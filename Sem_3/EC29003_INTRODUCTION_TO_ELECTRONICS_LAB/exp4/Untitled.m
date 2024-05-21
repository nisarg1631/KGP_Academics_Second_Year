x=[12,9,6,3,0,-3,-6,-9,-12];
y=[-12,-12,-12,-6,0,6,12,12,12];
%sys=tf([1e-2,0],[1e-4,1e-2,1e5]);
%options = bodeoptions;
%options.FreqUnits = 'Hz';
%bodemag(sys,options)
plot(x,y,'-o','MarkerSize',7,'MarkerFaceColor','r')
%semilogx(x,y,'-o','MarkerSize',7,'MarkerFaceColor','r')
%grid on
%semilogx(x,y,'-o',x1,y1,'--',8.49,2.343,'r*',12.9e6,2.343,'r*','MarkerSize',7,'MarkerFaceColor','b')
%text(10,21,['Lower cutoff frequency',newline,'8.82Hz'])
%text(5000,21,['Upper cutoff frequency',newline,'1.67MHz']
line([0 0], ylim);
line(xlim, [0 0]);
xlabel("V_{in}(volt)")
ylabel("V_{out}(volt)")
title("Voltage Transfer Characteristics")
