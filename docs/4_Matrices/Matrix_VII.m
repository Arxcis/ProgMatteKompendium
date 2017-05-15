%% The power method
clear
clc

n = 0; e = 1;
A = [0.9 0.3; 0.1 0.7];
u = [1 0]';
while e >= 1e-5
    t = A*u;
    e = max(u - t);
    u = t;
    n = n + 1;
end
disp([int2str(n), ' iterations']);
u

%% The QR algorithm
clear
clc
n = 0;
A = [12 -51 4; 6 167 -68; -4 24 -41];
% A = [.8 .3; .2 .7];
while abs(sum(reshape(tril(A,-1),[],1)))>1e-5
    [Q, R] = qr(A);
    A = Q'*A*Q;
    n = n + 1;
end
disp([int2str(n), ' iterations']);
A

%% Principal component analysis
clear
clc

x1 = [1 0 -1 0]';
x2 = [-1 1 0 0]';
X = [x1 x2] % Original data set
n = size(X,1); % number of observations for each variable
EX = mean(X,1); % Column mean
B = X-ones(n,1)*EX; % Centered dataset
C = B'*B/(n-1); % Covariance matrix
[Q, D] = eig(C);
[~, IX] = sort(diag(D),'descend'); % Rearrange the eigenvalues in descending order and rearrange the eigenvectors accordingly
Q = Q(:,IX); % eigenvectors of C (covariance matrix)
P = X*Q % X (original data matrix), P (principal components)
Xr = P*Q' % reconstruct X from P (principal components) and Q (eigenvectors of C)

%% Singular value decomposition in jmage compression
clear
clc

A = imread('4.2.04.tiff');
A = im2double(rgb2gray(A));
A = A(:,128:383);
[U, S, V] = svd(A);
n = 100; % number of singular vectors reserved
A2 = U(:,1:n)*S(1:n,1:n)*V(:,1:n)';
figure;
subplot(1,2,1), imshow(A), title('Original');
subplot(1,2,2), imshow(A2), title('Restored image after SVD');