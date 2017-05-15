%% Eigen faces
clear all
close all
clc

nIMG = 40; % number of face images
for i = 1 : nIMG
    I(:,:,i) = double(imread(['faces/',int2str(i),'.bmp'])); % Read the images
end

[m,n,~] = size(I);
X = reshape(I,[],nIMG)';
EX = mean(X,1);
B = X-ones(nIMG,1)*EX;
C = B'*B/(m*n-1);
[Q, D] = eig(C);
[d, IX] = sort(diag(D),'descend');
Q = Q(:,IX);

p = size(Q,2);
r = 1;
j = p + 1;
while r >= 0.9
    j = j - 1;
    r = sum(d(1:j))/sum(d);
end
L = j + 1;

k = L;
P = Q(:,1:k)'*B';
Xr = Q(:,1:k)*P;
I2 = reshape(Xr+EX'*ones(1,nIMG),m,n,[]);

figure(1);
imshow(reshape(EX,m,n),[]); % The "Mean" face
title('The mean face');

figure(2);
for i = 1 : 40
    subplot(5,8,i);
    imshow(reshape(Q(:,i),m,n),[]); % The eigenfaces
    title(['Eigenface ',int2str(i)]);
end

figure(3),
for i = 1 : 40
    subplot(5,8,i);
    imshow(I(:,:,i),[]); % The original faces
    title(['Face ',int2str(i)]);
end

figure(4),
for i = 1 : 40
    subplot(5,8,i);
    imshow(I2(:,:,i),[0 255]);  % The reproduced faces
    title(['rpdFace ',int2str(i)]);
end