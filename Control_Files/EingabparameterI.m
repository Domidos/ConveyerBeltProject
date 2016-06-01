%% Eingabeparameter für Motor laut Datenblatt

% Gemessene Werte

UN = 18;            % Nennspannung [V]
n0 = 5300;          % Leerlaufdrehzhal [rpm]
MA = 0.101;         % Anlaufmoment [Nm]
I0 = 0.025;         % Leerlaufstrom [A]
UA = 0.2;           % Anlaufspannung [V]


% Motorspezifische Parameter

k1 = 3.4/(1000/60); % Gegen-EMK [V/s^-1]
k2 = 0.0325;        % Drehmomentkonstante [Nm/A]
RA = 5.8;           % Ankerwiderstand [Ohm]
LA = 0.00075;       % Ankerinduktivität [H]
JR = 0.00000198;    % Rototträgheitsmoment[kg*m^2]

% Berechnete Werte

MR = k2*I0;         % Reibmoment [Nm]
tel = LA/RA;        % Elektrische Zeitkonstanze [s]

% Angenommene Werte

ML = 5e-4;             % Lastmoment [Nm]

% Drehzahlregler

TRI1 = 0.05;        % Abtastrate Istdrehzahl
KRI1 = 0.03;        % Reglerverstärkung
TN1  = 3.5;          % Reglerzetikonstante

% Stromregler

TRI2 = 0.005;        % Abtastrate MotorISTStrom
KRI2 = 0.015;        % Reglerverstärkung
TN2  = 0.25;          % Reglerzetikonstante