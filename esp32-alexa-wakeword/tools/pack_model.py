#!/usr/bin/env python3
"""
pack_model.py - ESP-SR Model Packing Tool

This script packs ESP-SR wake word models into a binary format
that can be flashed to ESP32-S3.

Usage:
    python pack_model.py -m <model_dir> -o <output_file>

Example:
    python pack_model.py -m srmodels -o srmodels.bin

Requirements:
    - ESP-SR repository cloned
    - Model files in the specified directory
"""

import argparse
import os
import sys
import struct
import json
from pathlib import Path


def pack_model(model_dir, output_file):
    """
    Pack model files into a binary format
    
    Args:
        model_dir: Directory containing model files
        output_file: Output binary file path
    """
    print(f"Packing models from: {model_dir}")
    print(f"Output file: {output_file}")
    
    model_path = Path(model_dir)
    if not model_path.exists():
        print(f"Error: Model directory '{model_dir}' does not exist!")
        return False
    
    # Find all model files
    model_files = []
    for ext in ['*.model', '*.bin', '*.json']:
        model_files.extend(model_path.glob(ext))
    
    if not model_files:
        print(f"Warning: No model files found in '{model_dir}'")
        print("Looking for: *.model, *.bin, *.json")
        return False
    
    print(f"Found {len(model_files)} model file(s):")
    for f in model_files:
        print(f"  - {f.name} ({f.stat().st_size} bytes)")
    
    # Create output binary
    with open(output_file, 'wb') as out:
        # Write header
        magic = b'ESPM'  # ESP Model magic number
        version = 1
        num_files = len(model_files)
        
        out.write(magic)
        out.write(struct.pack('<I', version))
        out.write(struct.pack('<I', num_files))
        
        # Write file table
        offset = 12 + (num_files * 64)  # Header + file table
        for model_file in model_files:
            name = model_file.name.encode('utf-8')[:56]
            size = model_file.stat().st_size
            
            out.write(name.ljust(56, b'\x00'))
            out.write(struct.pack('<I', offset))
            out.write(struct.pack('<I', size))
            
            offset += size
        
        # Write file data
        for model_file in model_files:
            with open(model_file, 'rb') as f:
                out.write(f.read())
    
    output_size = Path(output_file).stat().st_size
    print(f"\n✓ Model packed successfully!")
    print(f"Output size: {output_size} bytes ({output_size / 1024:.2f} KB)")
    return True


def main():
    parser = argparse.ArgumentParser(
        description='Pack ESP-SR wake word models',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python pack_model.py -m srmodels -o srmodels.bin
  python pack_model.py -m esp-sr/model/wakenet9 -o alexa_model.bin

Note:
  This is a simplified packing tool. For production use, refer to
  the official ESP-SR documentation and tools.
        """
    )
    
    parser.add_argument('-m', '--model-dir', 
                        required=True,
                        help='Directory containing model files')
    parser.add_argument('-o', '--output',
                        required=True,
                        help='Output binary file')
    
    args = parser.parse_args()
    
    success = pack_model(args.model_dir, args.output)
    sys.exit(0 if success else 1)


if __name__ == '__main__':
    main()
