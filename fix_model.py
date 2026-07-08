import h5py

print("Patching model...")
f = h5py.File("keras_model.h5", mode="r+")
model_config_string = f.attrs.get("model_config")

if model_config_string.find('"groups": 1,') != -1:
    model_config_string = model_config_string.replace('"groups": 1,', '')
    f.attrs.modify('model_config', model_config_string)
    f.flush()
    print("✅ Model fixed! You can now run teachable_unlock.py")
else:
    print("No 'groups: 1' found. It might already be fixed.")