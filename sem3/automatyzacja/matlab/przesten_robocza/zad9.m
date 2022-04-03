disp("Różnica odpowiadających sobie poszczególnych elemntów tablic: ");
disp(AB(:,:,1) - AB(:,:,2));
disp("Macierz o wymiarach nx4 składającej się ze wszystkich pionowych krawędzi tablicy trójwymiarowej: ");
disp([AB(:,1:2:3,1),AB(:,1:2:3,2)]);
disp("Podwojenie wartości elementów tablicy zwartych w „obszarze” 2x2x2: ");
disp(AB(2:3,2:3,1:2)*2);

