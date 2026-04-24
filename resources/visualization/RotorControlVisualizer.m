classdef RotorControlVisualizer < matlab.System
    % Combined swashplate + tail rotor live visualizer.
    %
% Inputs to the block:
%   theta0  : main rotor collective pitch [rad]
%   theta1c : main rotor longitudinal/cos cyclic pitch [rad]
%   theta1s : main rotor lateral/sin cyclic pitch [rad]
    %   theta0T : tail rotor collective pitch [rad]
    %   psiT    : tail rotor azimuth [rad]
    %   omegaT  : tail rotor angular speed [rad/s]
    %   rotDir  : tail rotor rotation direction flag. Use +1 or -1. Use 0
    %             to infer direction from omegaT.

    properties(Nontunable)
        SwashViewAzimuth (1,1) double = -135.0
        SwashViewElevation (1,1) double = 25.0
        TailViewAzimuth (1,1) double = -45.0
        TailViewElevation (1,1) double = 25.0
        UpdateEvery (1,1) double = 2.0

        SwashRadius (1,1) double = 1.0
        SwashHeightScale (1,1) double = 8.0
        SwashTiltScale (1,1) double = 3.0
        SwashAxisXYLimit (1,1) double = 1.35
        SwashFixedZLimit (1,1) double = 2.0
        ActuatorRadius (1,1) double = 0.055
        ActuatorBaseZ (1,1) double = -1.15
        ActuatorTopZ (1,1) double = -0.50
        CollectivePitchMin (1,1) double = 0.0
        CollectivePitchMax (1,1) double = 14.0 * pi / 180.0
        NormalVectorLength (1,1) double = 0.45

        TailRotorRadius (1,1) double = 1.0
        TailBladeCount (1,1) double = 4.0
        TailAxisLimit (1,1) double = 1.35
        TailPitchLimit (1,1) double = 20.0 * pi / 180.0
        TailHubGapRatio (1,1) double = 0.18
        TailBladeChordRatio (1,1) double = 0.18
        TailBladeThicknessRatio (1,1) double = 0.12
        TailThrustArrowMaxLength (1,1) double = 0.9
    end

    properties(Access = private)
        Fig
        SwashAx
        TailAx

        SwashRimLine
        SwashCenterPoint
        SwashNormalLine
        SwashCollectivePathLine
        SwashCollectiveMarker
        SwashCollectiveLimitMarkers
        SwashServoLines
        SwashActuatorCylinders
        SwashPhaseLines
        SwashPhaseLabels

        TailDiskLine
        TailHubPoint
        TailShaftLine
        TailThrustArrow
        TailThrustLabel
        TailBladeSurfaces
        TailBladeLabels

        StepCount = 0
        Phi
    end

    methods(Access = protected)
        function setupImpl(obj)
            obj.Phi = linspace(0.0, 2.0 * pi, 121);

            obj.Fig = figure( ...
                'Name', 'Rotor Control Visualizer', ...
                'Color', 'w', ...
                'NumberTitle', 'off');

            obj.SwashAx = subplot(1, 2, 1, 'Parent', obj.Fig);
            setup_swash_axes(obj);
            create_swash_graphics(obj);

            obj.TailAx = subplot(1, 2, 2, 'Parent', obj.Fig);
            setup_tail_axes(obj);
            create_tail_graphics(obj);
        end

        function stepImpl(obj, theta0, theta1c, theta1s, theta0T, psiT, omegaT, rotDir)
            obj.StepCount = obj.StepCount + 1;
            if mod(obj.StepCount, max(1, obj.UpdateEvery)) ~= 0
                return;
            end

            if isempty(obj.Fig) || ~isvalid(obj.Fig)
                setupImpl(obj);
            end

            update_swash(obj, theta0, theta1c, theta1s);
            update_tail(obj, theta0T, psiT, omegaT, rotDir);
            drawnow limitrate;
        end

        function resetImpl(obj)
            obj.StepCount = 0;
        end
    end

    methods(Access = private)
        function setup_swash_axes(obj)
            hold(obj.SwashAx, 'on');
            grid(obj.SwashAx, 'on');
            axis(obj.SwashAx, 'vis3d');
            xlabel(obj.SwashAx, 'x forward / cos');
            ylabel(obj.SwashAx, 'y left / sin');
            zlabel(obj.SwashAx, 'swash height');
            title(obj.SwashAx, 'Main Rotor Swashplate');
            view(obj.SwashAx, obj.SwashViewAzimuth, obj.SwashViewElevation);

            xlim(obj.SwashAx, [-obj.SwashAxisXYLimit obj.SwashAxisXYLimit] * obj.SwashRadius);
            ylim(obj.SwashAx, [-obj.SwashAxisXYLimit obj.SwashAxisXYLimit] * obj.SwashRadius);
            zlim(obj.SwashAx, [-obj.SwashFixedZLimit obj.SwashFixedZLimit]);
            pbaspect(obj.SwashAx, [1.0 1.0 0.85]);
            set(obj.SwashAx, ...
                'XLimMode', 'manual', ...
                'YLimMode', 'manual', ...
                'ZLimMode', 'manual', ...
                'CameraViewAngleMode', 'manual');
        end

        function setup_tail_axes(obj)
            hold(obj.TailAx, 'on');
            grid(obj.TailAx, 'on');
            axis(obj.TailAx, 'vis3d');
            xlabel(obj.TailAx, 'shaft x');
            ylabel(obj.TailAx, 'disk y');
            zlabel(obj.TailAx, 'disk z');
            title(obj.TailAx, 'Tail Rotor');
            view(obj.TailAx, obj.TailViewAzimuth, obj.TailViewElevation);

            lim = obj.TailAxisLimit * obj.TailRotorRadius;
            xlim(obj.TailAx, [-lim lim]);
            ylim(obj.TailAx, [-lim lim]);
            zlim(obj.TailAx, [-lim lim]);
            pbaspect(obj.TailAx, [1.0 1.0 1.0]);
            set(obj.TailAx, ...
                'XLimMode', 'manual', ...
                'YLimMode', 'manual', ...
                'ZLimMode', 'manual', ...
                'CameraViewAngleMode', 'manual');
        end

        function create_swash_graphics(obj)
            obj.SwashRimLine = plot3(obj.SwashAx, zeros(size(obj.Phi)), ...
                zeros(size(obj.Phi)), zeros(size(obj.Phi)), ...
                'LineWidth', 2.0, 'Color', [0.0 0.45 0.74]);
            obj.SwashCenterPoint = plot3(obj.SwashAx, 0.0, 0.0, 0.0, 'o', ...
                'MarkerSize', 8, ...
                'MarkerFaceColor', [0.85 0.33 0.10], ...
                'MarkerEdgeColor', [0.85 0.33 0.10]);
            obj.SwashNormalLine = quiver3(obj.SwashAx, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.0, ...
                'LineWidth', 2.3, ...
                'MaxHeadSize', 0.9, ...
                'Color', [0.47 0.67 0.19]);

            z_col_min = obj.SwashHeightScale * obj.CollectivePitchMin;
            z_col_max = obj.SwashHeightScale * obj.CollectivePitchMax;
            obj.SwashCollectivePathLine = plot3(obj.SwashAx, ...
                [0.0 0.0], [0.0 0.0], [z_col_min z_col_max], ...
                '--', 'LineWidth', 1.5, 'Color', [0.15 0.15 0.15]);
            obj.SwashCollectiveLimitMarkers = plot3(obj.SwashAx, ...
                [0.0 0.0], [0.0 0.0], [z_col_min z_col_max], ...
                's', ...
                'MarkerSize', 7, ...
                'MarkerFaceColor', [0.15 0.15 0.15], ...
                'MarkerEdgeColor', [0.15 0.15 0.15], ...
                'LineStyle', 'none');
            obj.SwashCollectiveMarker = plot3(obj.SwashAx, 0.0, 0.0, 0.0, 'o', ...
                'MarkerSize', 9, ...
                'MarkerFaceColor', [0.93 0.69 0.13], ...
                'MarkerEdgeColor', [0.30 0.30 0.30]);

            obj.SwashActuatorCylinders = gobjects(3, 1);
            obj.SwashServoLines = gobjects(3, 1);
            for i = 1:3
                phi_i = 2.0 * pi * (i - 1.0) / 3.0;
                xs = obj.SwashRadius * cos(phi_i);
                ys = obj.SwashRadius * sin(phi_i);
                [xc, yc, zc] = actuator_cylinder(obj, xs, ys, obj.ActuatorBaseZ, obj.ActuatorTopZ);
                obj.SwashActuatorCylinders(i) = surf(obj.SwashAx, xc, yc, zc, ...
                    'FaceColor', [0.35 0.35 0.35], ...
                    'EdgeColor', 'none', ...
                    'FaceLighting', 'gouraud');
                obj.SwashServoLines(i) = plot3(obj.SwashAx, [0.0 0.0], [0.0 0.0], [0.0 0.0], ...
                    'LineWidth', 2.2, 'Color', [0.55 0.55 0.55]);
            end

            obj.SwashPhaseLines = gobjects(4, 1);
            obj.SwashPhaseLabels = gobjects(4, 1);
            colors = lines(4);
            for b = 1:4
                obj.SwashPhaseLines(b) = plot3(obj.SwashAx, [0.0 0.0], [0.0 0.0], [0.0 0.0], ...
                    'LineWidth', 1.5, 'Color', colors(b, :));
                obj.SwashPhaseLabels(b) = text(obj.SwashAx, 0.0, 0.0, 0.0, swash_blade_label(b), ...
                    'FontSize', 12, ...
                    'FontWeight', 'bold', ...
                    'Color', colors(b, :), ...
                    'HorizontalAlignment', 'center', ...
                    'VerticalAlignment', 'middle');
            end
        end

        function create_tail_graphics(obj)
            obj.TailDiskLine = plot3(obj.TailAx, zeros(size(obj.Phi)), ...
                zeros(size(obj.Phi)), zeros(size(obj.Phi)), ...
                'LineWidth', 2.0, 'Color', [0.0 0.45 0.74]);
            obj.TailHubPoint = plot3(obj.TailAx, 0.0, 0.0, 0.0, 'o', ...
                'MarkerSize', 8, ...
                'MarkerFaceColor', [0.85 0.33 0.10], ...
                'MarkerEdgeColor', [0.85 0.33 0.10]);
            obj.TailShaftLine = plot3(obj.TailAx, [-1.1 1.1] * obj.TailRotorRadius, ...
                [0.0 0.0], [0.0 0.0], ...
                '--', 'LineWidth', 1.5, 'Color', [0.20 0.20 0.20]);
            obj.TailThrustArrow = quiver3(obj.TailAx, 0.0, 0.0, 0.0, 0.4, 0.0, 0.0, 0.0, ...
                'LineWidth', 2.3, ...
                'MaxHeadSize', 0.9, ...
                'Color', [0.47 0.67 0.19]);
            obj.TailThrustLabel = text(obj.TailAx, 0.45, 0.0, 0.0, 'T_T', ...
                'FontSize', 12, ...
                'FontWeight', 'bold', ...
                'Color', [0.25 0.45 0.10], ...
                'HorizontalAlignment', 'center');

            obj.TailBladeSurfaces = gobjects(obj.TailBladeCount, 1);
            obj.TailBladeLabels = gobjects(obj.TailBladeCount, 1);
            colors = lines(obj.TailBladeCount);
            for b = 1:obj.TailBladeCount
                obj.TailBladeSurfaces(b) = surf(obj.TailAx, zeros(2, 2), zeros(2, 2), zeros(2, 2), ...
                    'FaceColor', colors(b, :), ...
                    'EdgeColor', 'none', ...
                    'FaceAlpha', 0.88, ...
                    'FaceLighting', 'gouraud');
                obj.TailBladeLabels(b) = text(obj.TailAx, 0.0, 0.0, 0.0, num2str(b), ...
                    'FontSize', 11, ...
                    'FontWeight', 'bold', ...
                    'Color', colors(b, :), ...
                    'HorizontalAlignment', 'center', ...
                    'VerticalAlignment', 'middle');
            end
        end

        function update_swash(obj, theta0, theta1c, theta1s)
            R = obj.SwashRadius;
            x = R * cos(obj.Phi);
            y = R * sin(obj.Phi);

            z0 = obj.SwashHeightScale * theta0;
            ax_tilt = obj.SwashTiltScale * theta1c;
            ay_tilt = obj.SwashTiltScale * theta1s;
            z = z0 + ax_tilt * x + ay_tilt * y;

            set(obj.SwashRimLine, 'XData', x, 'YData', y, 'ZData', z);
            set(obj.SwashCenterPoint, 'XData', 0.0, 'YData', 0.0, 'ZData', z0);
            set(obj.SwashCollectiveMarker, 'XData', 0.0, 'YData', 0.0, 'ZData', z0);

            normal_vec = [-ax_tilt; -ay_tilt; 1.0];
            normal_vec = normal_vec / norm(normal_vec);
            normal_len = R * obj.NormalVectorLength;
            set(obj.SwashNormalLine, ...
                'XData', 0.0, ...
                'YData', 0.0, ...
                'ZData', z0, ...
                'UData', normal_len * normal_vec(1), ...
                'VData', normal_len * normal_vec(2), ...
                'WData', normal_len * normal_vec(3));

            for i = 1:3
                phi_i = 2.0 * pi * (i - 1.0) / 3.0;
                xs = R * cos(phi_i);
                ys = R * sin(phi_i);
                zs = z0 + ax_tilt * xs + ay_tilt * ys;
                set(obj.SwashServoLines(i), ...
                    'XData', [xs xs], ...
                    'YData', [ys ys], ...
                    'ZData', [obj.ActuatorTopZ zs]);
            end

            for b = 1:4
                psi_b = 2.0 * pi * (b - 1.0) / 4.0;
                xb = [0.0, R * cos(psi_b)];
                yb = [0.0, R * sin(psi_b)];
                zb_tip = z0 + ax_tilt * xb(2) + ay_tilt * yb(2);
                set(obj.SwashPhaseLines(b), ...
                    'XData', xb, ...
                    'YData', yb, ...
                    'ZData', [z0, zb_tip]);
                set(obj.SwashPhaseLabels(b), ...
                    'Position', [1.08 * xb(2), 1.08 * yb(2), zb_tip + 0.04]);
            end
        end

        function update_tail(obj, theta0T, psiT, omegaT, rotDir)
            R = obj.TailRotorRadius;
            y_disk = R * cos(obj.Phi);
            z_disk = R * sin(obj.Phi);
            set(obj.TailDiskLine, ...
                'XData', zeros(size(obj.Phi)), ...
                'YData', y_disk, ...
                'ZData', z_disk);

            pitch_frac = theta0T / max(obj.TailPitchLimit, 1.0e-6);
            pitch_frac = min(max(pitch_frac, -1.0), 1.0);
            thrust_len = obj.TailThrustArrowMaxLength * R * pitch_frac;
            set(obj.TailThrustArrow, ...
                'XData', 0.0, ...
                'YData', 0.0, ...
                'ZData', 0.0, ...
                'UData', thrust_len, ...
                'VData', 0.0, ...
                'WData', 0.0);
            set(obj.TailThrustLabel, ...
                'Position', [thrust_len + 0.10 * sign_nonzero(thrust_len) * R, 0.0, 0.0]);

            if abs(rotDir) > 0.5
                rotation_sign = sign_nonzero(rotDir);
            else
                rotation_sign = sign_nonzero(omegaT);
            end
            pitch_vis = max(min(theta0T, obj.TailPitchLimit), -obj.TailPitchLimit);

            for b = 1:obj.TailBladeCount
                psi_b = psiT + 2.0 * pi * (b - 1.0) / obj.TailBladeCount;
                [xb, yb, zb] = tail_blade_airfoil_surface(obj, psi_b, pitch_vis, rotation_sign);
                set(obj.TailBladeSurfaces(b), 'XData', xb, 'YData', yb, 'ZData', zb);

                y_tip = R * cos(psi_b);
                z_tip = R * sin(psi_b);
                set(obj.TailBladeLabels(b), ...
                    'Position', [0.0, 1.10 * y_tip, 1.10 * z_tip]);
            end
        end

        function [x, y, z] = actuator_cylinder(obj, x0, y0, z_base, z_top)
            phi = linspace(0.0, 2.0 * pi, 32);
            r = obj.ActuatorRadius;
            if abs(z_top - z_base) < 1.0e-6
                z_top = z_base + 1.0e-6;
            end

            x = x0 + r * [cos(phi); cos(phi)];
            y = y0 + r * [sin(phi); sin(phi)];
            z = [z_base * ones(size(phi)); z_top * ones(size(phi))];
        end

        function [x, y, z] = tail_blade_airfoil_surface(obj, psi_b, pitch_angle, rotation_sign)
            R = obj.TailRotorRadius;
            r_root = obj.TailHubGapRatio * R;
            r_tip = 0.98 * R;
            span = linspace(r_root, r_tip, 5);

            x_af = linspace(0.0, 1.0, 11);
            yt = 5.0 * obj.TailBladeThicknessRatio * ( ...
                0.2969 * sqrt(max(x_af, 1.0e-6)) ...
                - 0.1260 * x_af ...
                - 0.3516 * x_af.^2 ...
                + 0.2843 * x_af.^3 ...
                - 0.1015 * x_af.^4);
            perimeter_chord = [x_af, fliplr(x_af)];
            perimeter_thick = [yt, -fliplr(yt)];

            n_perim = numel(perimeter_chord);
            n_span = numel(span);
            x = zeros(n_perim, n_span);
            y = zeros(n_perim, n_span);
            z = zeros(n_perim, n_span);

            radial = [0.0; cos(psi_b); sin(psi_b)];
            tangent = rotation_sign * [0.0; -sin(psi_b); cos(psi_b)];
            shaft = [1.0; 0.0; 0.0];

            chord_axis = cos(pitch_angle) * tangent + sin(pitch_angle) * shaft;
            thick_axis = -sin(pitch_angle) * tangent + cos(pitch_angle) * shaft;

            for j = 1:n_span
                chord = R * obj.TailBladeChordRatio;
                center = span(j) * radial;

                for k = 1:n_perim
                    chord_offset = (0.5 - perimeter_chord(k)) * chord;
                    thick_offset = perimeter_thick(k) * chord;
                    point = center + chord_offset * chord_axis + thick_offset * thick_axis;
                    x(k, j) = point(1);
                    y(k, j) = point(2);
                    z(k, j) = point(3);
                end
            end
        end
    end
end

function label = swash_blade_label(blade_index)
labels = {'C', 'D', 'A', 'B'};
label = labels{blade_index};
end

function s = sign_nonzero(x)
if x < 0.0
    s = -1.0;
else
    s = 1.0;
end
end
