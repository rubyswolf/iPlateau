<!-- Version 4. Remove this tag to avoid automatic overwriting with new versions -->

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
- `ifact doxy find iPlug2 "<regex query>" [options]`
- Find options: `--type <kind>`, `--limit <N>`, `--name-only`, `--no-desc`
- `ifact doxy lookup iPlug2 <symbol> (feature)`
- Leave `feature` blank for a summary; includes constructors, methods, and fields.
- Symbol names support `Class::Method` syntax.

## Code Search
- Use `rg` to find/read source code.
- Apply search limits to avoid flooding context.

## Info Topics
- Use `ifact info <topic>` for every relevant area, even if familiar.
- Do not reread a topic if you still remember it.
- Follow referenced subtopics when relevant.

Available topics:
- `manage`: Project-level control, creating/managing plugins and tools.
- `ui`: Plugin interface design and creation.
- `dsp`: Signal processing implementation.
- `parameter`: Parameter creation/management and efficient DSP access.
- `preset`: Built-in preset creation.
- `serialize`: Persisting arbitrary plugin state across DAW sessions.
