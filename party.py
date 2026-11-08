# Party Vibes Hub - A collaborative playground for Git practice

def get_vibes():
    return [
        "Coding at 3 AM with zero bugs (definitely a lie).",
        "Coffee level: Critical mass.",
        "Git push --force: Living dangerously."
    ]

def main():
    print("=== Welcome to the Party Vibes Hub ===")
    print("Current Vibes:")
    vibes = get_vibes()
    for i, vibe in enumerate(vibes, 1):
        print(f"  {i}. {vibe}")
    print("\n---------------------------------------")
    print("Collaboration makes coding better!")

if __name__ == "__main__":
    main()