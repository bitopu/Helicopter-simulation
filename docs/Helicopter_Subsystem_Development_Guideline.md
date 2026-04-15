# Helicopter Aerodynamic Subsystem Development Guideline

This project is developed in MATLAB/Simulink with the main model in `resources/simulink/Helicopter_Model.slx` and the interface list in `resources/interface/interface_simulink_block.xlsx`. Use the project file `Helicopter.prj` to open the environment. The rule is simple: every subsystem update must keep parameters, interfaces, and model behavior synchronized.

## 1. Update Parameters

Before changing any aerodynamic logic, define the parameter set clearly: name, symbol, unit, nominal value, valid range, source, and subsystem owner. Keep one source of truth for each parameter in MATLAB or Simulink, such as the model workspace, mask parameters, or a dedicated initialization script. Do not duplicate constants across blocks because that quickly creates inconsistent behavior. Use SI units unless another unit is required by an external interface, and document any conversion at the boundary. When a parameter changes, also review dependent gains, lookup tables, trim values, and limit checks. The change is complete only when the model initializes cleanly and the baseline simulation still runs without unexpected warnings.

## 2. Update Interface

Update `resources/interface/interface_simulink_block.xlsx` before, or at the same time as, changing ports in the model. Each interface entry should define the subsystem name, signal name, direction, description, unit, data type, dimension, sample time, and default or fail-safe value. Keep port order stable whenever possible to avoid breaking connected subsystems. If an interface must change, update all downstream connections in `Helicopter_Model.slx` in the same change set. Prefer named signals and buses for larger interfaces instead of anonymous mux lines. After the interface update, run model checks to confirm signal dimensions, data types, rates, and units are still consistent.

## 3. Update Subsystem And Push Code

Open `resources/simulink/Helicopter_Model.slx`, modify only the target aerodynamic subsystem, and keep each subsystem focused on one responsibility. Separate parameter loading, interface mapping, and aerodynamic equations so the model stays readable and testable. Avoid hiding new constants inside random block dialogs; connect them through the approved parameter source. After editing, verify that the subsystem compiles, the model loads, nominal simulation works, and outputs keep the expected sign, scale, and unit. Then review the git diff and commit only intended files. A standard workflow is:

```powershell
git status
git add docs/Helicopter_Subsystem_Development_Guideline.md
git add resources/simulink/Helicopter_Model.slx
git add resources/interface/interface_simulink_block.xlsx
git commit -m "Add helicopter subsystem development guideline"
git push origin master
```

If only documentation changes, stage only the guideline file. Do not commit temporary content such as `resources/tmp/` unless it is an intentional test artifact.
