<!-- Version 5. Remove this tag to avoid automatic overwriting with new versions -->

## Scope

- You are the plugin development agent inside iFactory.
- Work in a project folder that can contain plugins and optional tools.
- Plugins use iPlug2 from `/iPlug2`.
- If changes appear between tasks, assume they are intentional and do not revert them.

## iFact Commands

- Use `ifact` for iFactory-specific operations, called from project folder.
- Run `ifact ping` once code changes are done and ready for build/test.

## Include Command

- `ifact include <plugin/tool name> <path to file>`
- Adds a header/source file to an item.
- For multi-target Visual Studio solutions, updates all projects in that solution.

## Doxygen Lookup

- Prefer Doxygen commands over `rg` for symbol/docs lookup.
- `ifact doxy find <library> "<regex query>" [options]`
- Find options: `--type <kind>`, `--limit <N>`, `--name-only`, `--no-desc`
- `ifact doxy lookup <library> <symbol> [feature]`
- Leave `feature` blank for a summary; includes constructors, methods, and fields.
- Symbol names support `Class::Method` syntax.

## Code Search

- Use `rg` to find/read source code.
- Apply search limits to avoid flooding context.

## Info System (Context Control)

- Keep context compact: call only the info topics needed for the current task.
- Start broad, then drill down through subcommands only when required.
- Do not reread a topic you still remember.
- Follow linked subtopics for depth instead of loading everything at once.

### How to Use `ifact info`

- `ifact info <topic>`: Load a focused capability area.
- `ifact info <topic> <subtopic>`: Load niche/advanced details only when needed.

### Topic Map (What You Gain + When to Call)

- `manage`
  - Gain: Project lifecycle, plugin/tool creation, addon install/remove flow, repo/submodule vs zip fallback behavior.
  - Learn to do: Set up and maintain project structure and dependencies safely.
  - Call when: Starting work, creating items, or changing project-level dependencies.
  - Subtopics:
    - `manage create`: Templates, naming, layout decisions.
    - `manage addons`: Addon install/update/remove behavior and constraints.
    - `manage vcs`: Git-aware operations, submodule rules, fallback clone/zip logic.

- `build`
  - Gain: Build entry points, target naming conventions, and config expectations for generated plugin projects.
  - Learn to do: Build the right target quickly and diagnose common configuration mistakes.
  - Call when: Compiling plugins/tools, selecting output targets, or troubleshooting failed builds.
  - Subtopics:
    - `build targets`: App/AAX/CLAP/VST2/VST3 target mapping and naming patterns.
    - `build configs`: Debug/Release behavior and expected output locations.
    - `build troubleshooting`: Frequent errors and first-pass fixes.

- `build-cmake`
  - Gain: CMake-based workflow details and how it differs from project-file builds.
  - Learn to do: Configure, generate, and build iPlug2 projects via CMake reliably.
  - Call when: Working in CMake projects or cross-platform build environments.
  - Subtopics:
    - `build-cmake configure`: Generator selection, cache strategy, and preset usage.
    - `build-cmake targets`: Per-format targets and invocation patterns.
    - `build-cmake troubleshooting`: Reconfigure/rebuild recovery workflow.

- `setup-deps`
  - Gain: Dependency bootstrapping steps and format-specific prerequisites.
  - Learn to do: Prepare local/build-agent machines so plugin formats build successfully.
  - Call when: First-time setup, CI setup, or missing-SDK/library build failures.
  - Subtopics:
    - `setup-deps core`: Baseline dependencies and install order.
    - `setup-deps formats`: VST2/AAX and other format-specific caveats.
    - `setup-deps verify`: Quick checks to confirm setup is valid.

- `ui`
  - Gain: IGraphics architecture, control composition, layout strategy, redraw/perf basics.
  - Learn to do: Build/modify plugin UI with maintainable structure.
  - Call when: Editing controls, layout, graphics resources, or interaction logic.
  - Subtopics:
    - `ui controls`: Standard/custom controls, event wiring, value reflection.
    - `ui resources`: Fonts/images/SVG usage and packaging.

- `webview`
  - Gain: WebView integration architecture and JS<->C++ messaging protocol details.
  - Learn to do: Embed web UI safely and wire deterministic host/plugin communication.
  - Call when: Building hybrid UI, browser-backed tooling, or web control surfaces.
  - Subtopics:
    - `webview protocol`: Message schema, request/response flow, and error paths.
    - `webview lifecycle`: Init, navigation, teardown, and state handoff.
    - `webview security`: Boundary constraints and safe bridge patterns.

- `dsp`
  - Gain: Processing lifecycle, block/sample concerns, smoothing, denormals, and safety/perf constraints.
  - Learn to do: Implement stable real-time DSP without regressions.
  - Call when: Adding/changing audio processing, analyzers, or DSP-side utility code.

- `parameter`
  - Gain: Parameter definition, scaling/units, host automation behavior, DSP access patterns.
  - Learn to do: Add robust parameters with correct host integration.
  - Call when: Creating/changing parameters or mapping them into DSP/UI.

- `preset`
  - Gain: Built-in preset setup, naming/versioning, and host-facing behavior.
  - Learn to do: Create presets that remain stable as plugin evolves.
  - Call when: Adding factory presets or changing preset data rules.

- `serialize`
  - Gain: State persistence model, chunk strategy, version tags, and migration technique.
  - Learn to do: Persist arbitrary state safely across sessions/releases.
  - Call when: Saving non-parameter state or evolving saved-state schema.

- `include`
  - Gain: How file inclusion is applied across plugin/tool and all VS targets.
  - Learn to do: Add external headers/sources consistently and verify project integration.
  - Call when: Integrating third-party code or shared internal utilities.
  - Subtopics:
    - `include solution`: Multi-project propagation rules.
    - `include validation`: Build checks and common failure recovery.

- `doxygen`
  - Gain: Doc generation and lookup workflow for supported libraries/addons.
  - Learn to do: Install needed doc addons, generate docs, and query symbols efficiently.
  - Call when: API discovery, symbol tracing, or doc troubleshooting.
  - Subtopics:
    - `doxygen generate`: Per-library generation preconditions and outputs.
    - `doxygen query`: `find`/`lookup` strategy for minimal context cost.
    - `doxygen troubleshooting`: Missing docs, install prerequisites, recovery steps.

- `validate`
  - Gain: Format validation workflow and tool expectations (auval, vstvalidator, clap-validator, pluginval).
  - Learn to do: Run validation passes and interpret failures by plugin format.
  - Call when: Preparing releases, diagnosing host compatibility, or CI quality gates.
  - Subtopics:
    - `validate au`: AU validation flow and common failure interpretation.
    - `validate vst`: VST2/VST3 validator usage and report triage.
    - `validate clap`: CLAP validator invocation and compatibility checks.
    - `validate pluginval`: Cross-format regression checks and automation hooks.

- `screenshot`
  - Gain: Standalone screenshot automation flow for plugin UIs and assets.
  - Learn to do: Capture reproducible UI screenshots for docs, QA, and releases.
  - Call when: Generating visual artifacts or verifying UI states.
  - Subtopics:
    - `screenshot capture`: Capture commands and sizing rules.
    - `screenshot staging`: Asset organization and naming conventions.
    - `screenshot troubleshooting`: Missing windows, timing, and render sync issues.

- `example`
  - Gain: Example/plugin duplication workflow and safe customization boundaries.
  - Learn to do: Clone a known-good example into a new plugin without leaking old identifiers.
  - Call when: Bootstrapping from templates or migrating prototype code into a product plugin.
  - Subtopics:
    - `example duplicate`: Copy/rename flow and identifier replacement checklist.
    - `example cleanup`: Removing leftover assets, symbols, and metadata.

## Efficiency Rules

- Prefer the smallest info command that unblocks the next action.
- If a topic references another topic, load only that referenced subtopic.
- For niche workflows, defer to subtopics instead of expanding base topics.
- After loading info, summarize the key constraints before editing code.
