% This script is a modified version based on official fern implement by Matlab
% It not display figure with window but save it to a picture file

function [] = fern(step, outfile)

% Init start coord
x = [.5; .5];

% Init points for plot
px = zeros(step+1, 1);
py = zeros(step+1, 1);
px(1) = x(1);
py(1) = x(2);

% Setting transform matrix and probability
p  = [ .85  .92  .99  1.00];
A1 = [ .85  .04; -.04  .85];  b1 = [0; 1.6];
A2 = [ .20 -.26;  .23  .22];  b2 = [0; 1.6];
A3 = [-.15  .28;  .26  .24];  b3 = [0; .44];
A4 = [  0    0 ;   0   .16];

% Start iteration
cnt = 0;
tic
while cnt < step
   r = rand;
   if r < p(1)
      x = A1*x + b1;
   elseif r < p(2)
      x = A2*x + b2;
   elseif r < p(3)
      x = A3*x + b3;
   else
      x = A4*x;
   end
   px(cnt+2) = x(1);
   py(cnt+2) = x(2);
   cnt = cnt + 1;
   if mod(cnt, 1000) == 0
        disp(['Step ', num2str(cnt)]);
   end
end
t = toc;

% Save picture
figure('Visible','off');
set(gcf,'color','white','menubar','none', ...
   'numbertitle','off','name','Fractal Fern', ...
   'Units', 'pixels', 'Position', [5 5 1000 1000]);
set(gca, 'Position', [0.1, 0.1, 0.9, 0.9])
darkgreen = [0 2/3 0];
plot(px,py,'.','markersize',4,'color',darkgreen);
s = sprintf('%8.0f points in %6.3f seconds',cnt,t);
text(-1.5,-0.5,s,'fontweight','bold');
axis([-3 3 -0 11]);
axis off;
saveas(gcf, outfile);
