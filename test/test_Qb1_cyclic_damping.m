clc;
clear;
close all;

% Blade azimuths
psi = [0; pi/2; pi; 3*pi/2];

% Small perturbation
eps_val = 1e-4;

% Base state
beta0   = 0;
beta0_d = 0;
beta1c  = 0;
beta1s  = 0;

%% =========================
% Test damping wrt beta1c_d
%% =========================
beta1c_d_p = +eps_val;
beta1c_d_m = -eps_val;
beta1s_d   = 0;

[Qb0_p, Qb1c_p, Qb1s_p, Qb_p, beta_array_p, beta_dot_array_p] = ...
    Qb1_test_with_damping(beta0, beta0_d, beta1c, beta1s, beta1c_d_p, beta1s_d, psi);

[Qb0_m, Qb1c_m, Qb1s_m, Qb_m, beta_array_m, beta_dot_array_m] = ...
    Qb1_test_with_damping(beta0, beta0_d, beta1c, beta1s, beta1c_d_m, beta1s_d, psi);

dQb1c_dbeta1c_d = (Qb1c_p - Qb1c_m) / (2*eps_val);
dQb1s_dbeta1c_d = (Qb1s_p - Qb1s_m) / (2*eps_val);

fprintf('\n==============================\n');
fprintf('TEST 1: sensitivity to beta1c_d\n');
fprintf('==============================\n');
fprintf('Qb1c(beta1c_d = +eps) = %+12.6f\n', Qb1c_p);
fprintf('Qb1c(beta1c_d = -eps) = %+12.6f\n', Qb1c_m);
fprintf('dQb1c/dbeta1c_d       = %+12.6f\n', dQb1c_dbeta1c_d);
fprintf('\n');
fprintf('Qb1s(beta1c_d = +eps) = %+12.6f\n', Qb1s_p);
fprintf('Qb1s(beta1c_d = -eps) = %+12.6f\n', Qb1s_m);
fprintf('dQb1s/dbeta1c_d       = %+12.6f\n', dQb1s_dbeta1c_d);

%% =========================
% Test damping wrt beta1s_d
%% =========================
beta1c_d   = 0;
beta1s_d_p = +eps_val;
beta1s_d_m = -eps_val;

[Qb0_p2, Qb1c_p2, Qb1s_p2, Qb_p2, beta_array_p2, beta_dot_array_p2] = ...
    Qb1_test_with_damping(beta0, beta0_d, beta1c, beta1s, beta1c_d, beta1s_d_p, psi);

[Qb0_m2, Qb1c_m2, Qb1s_m2, Qb_m2, beta_array_m2, beta_dot_array_m2] = ...
    Qb1_test_with_damping(beta0, beta0_d, beta1c, beta1s, beta1c_d, beta1s_d_m, psi);

dQb1c_dbeta1s_d = (Qb1c_p2 - Qb1c_m2) / (2*eps_val);
dQb1s_dbeta1s_d = (Qb1s_p2 - Qb1s_m2) / (2*eps_val);

fprintf('\n==============================\n');
fprintf('TEST 2: sensitivity to beta1s_d\n');
fprintf('==============================\n');
fprintf('Qb1s(beta1s_d = +eps) = %+12.6f\n', Qb1s_p2);
fprintf('Qb1s(beta1s_d = -eps) = %+12.6f\n', Qb1s_m2);
fprintf('dQb1s/dbeta1s_d       = %+12.6f\n', dQb1s_dbeta1s_d);
fprintf('\n');
fprintf('Qb1c(beta1s_d = +eps) = %+12.6f\n', Qb1c_p2);
fprintf('Qb1c(beta1s_d = -eps) = %+12.6f\n', Qb1c_m2);
fprintf('dQb1c/dbeta1s_d       = %+12.6f\n', dQb1c_dbeta1s_d);

%% =========================
% Optional: displacement sensitivity
%% =========================
beta1c_p = +eps_val;
beta1c_m = -eps_val;
beta1s   = 0;
beta1c_d = 0;
beta1s_d = 0;

[~, Qb1c_bp, Qb1s_bp] = Qb1_test_with_damping(beta0, beta0_d, beta1c_p, beta1s, beta1c_d, beta1s_d, psi);
[~, Qb1c_bm, Qb1s_bm] = Qb1_test_with_damping(beta0, beta0_d, beta1c_m, beta1s, beta1c_d, beta1s_d, psi);

dQb1c_dbeta1c = (Qb1c_bp - Qb1c_bm)/(2*eps_val);
dQb1s_dbeta1c = (Qb1s_bp - Qb1s_bm)/(2*eps_val);

fprintf('\n==============================\n');
fprintf('TEST 3: sensitivity to beta1c\n');
fprintf('==============================\n');
fprintf('dQb1c/dbeta1c         = %+12.6f\n', dQb1c_dbeta1c);
fprintf('dQb1s/dbeta1c         = %+12.6f\n', dQb1s_dbeta1c);

beta1c = 0;
beta1s_p = +eps_val;
beta1s_m = -eps_val;

[~, Qb1c_sp, Qb1s_sp] = Qb1_test_with_damping(beta0, beta0_d, beta1c, beta1s_p, beta1c_d, beta1s_d, psi);
[~, Qb1c_sm, Qb1s_sm] = Qb1_test_with_damping(beta0, beta0_d, beta1c, beta1s_m, beta1c_d, beta1s_d, psi);

dQb1c_dbeta1s = (Qb1c_sp - Qb1c_sm)/(2*eps_val);
dQb1s_dbeta1s = (Qb1s_sp - Qb1s_sm)/(2*eps_val);

fprintf('\n==============================\n');
fprintf('TEST 4: sensitivity to beta1s\n');
fprintf('==============================\n');
fprintf('dQb1s/dbeta1s         = %+12.6f\n', dQb1s_dbeta1s);
fprintf('dQb1c/dbeta1s         = %+12.6f\n', dQb1c_dbeta1s);

%% =========================
% Interpretation notes
%% =========================
fprintf('\n==============================\n');
fprintf('INTERPRETATION\n');
fprintf('==============================\n');
fprintf('If aerodynamic damping is stabilizing:\n');
fprintf('- Qb1c should oppose beta1c_d according to your sign convention\n');
fprintf('- Qb1s should oppose beta1s_d according to your sign convention\n');
fprintf('- Cross-coupling slopes should usually be much smaller than direct slopes\n');
fprintf('\nCompare the sign of these slopes with the sign used in:\n');
fprintf('beta1c_dd = Qb1c/Ib + ...\n');
fprintf('beta1s_dd = Qb1s/Ib + ...\n');