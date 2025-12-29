import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class Day03 {

    static List<int[]> parse(String conteudo) {
        String[] linhas = conteudo.split("\\r?\\n");
        List<int[]> resultado = new ArrayList<>();

        for (String linha : linhas) {
            char[] chars = linha.toCharArray();
            int[] nums = new int[chars.length];

            for (int i = 0; i < chars.length; i++) {
                nums[i] = chars[i] - '0';
            }

            resultado.add(nums);
        }

        return resultado;
    }

    static void part01(String conteudo) {
        List<int[]> valores = parse(conteudo);
        int soma = 0;

        for (int[] linha : valores) {
            int impacto = maiorImpactoDaLinha(linha);
            soma += impacto;
        }

        System.out.println("Soma: " + soma);
    }

    static void part02(String conteudo) {
        List<int[]> valores = parse(conteudo);
        long soma = 0;

        for (int[] linha : valores) {
            long impacto = maiorImpacto12(linha);
            soma += impacto;
        }

        System.out.println("Soma total: " + soma);
    }

    static int maiorImpactoDaLinha(int[] nums) {
        int maiorValor = Integer.MIN_VALUE;
        int idxMaior = -1;

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > maiorValor) {
                maiorValor = nums[i];
                idxMaior = i;
            }
        }

        int segundoValor = Integer.MIN_VALUE;
        int idxSegundo = -1;

        for (int i = idxMaior + 1; i < nums.length; i++) {
            if (nums[i] > segundoValor) {
                segundoValor = nums[i];
                idxSegundo = i;
            }
        }

        if (idxSegundo == -1) {
            for (int i = 0; i < idxMaior; i++) {
                if (nums[i] > segundoValor) {
                    segundoValor = nums[i];
                    idxSegundo = i;
                }
            }
        }

        if (idxMaior < idxSegundo) {
            return Integer.parseInt("" + maiorValor + segundoValor);
        } else {
            return Integer.parseInt("" + segundoValor + maiorValor);
        }
    }

    static long maiorImpacto12(int[] nums) {
        int k = 12;
        List<Integer> stack = new ArrayList<>();
        int remover = nums.length - k;

        for (int atual : nums) {
            while (!stack.isEmpty() &&
                    remover > 0 &&
                    stack.get(stack.size() - 1) < atual) {
                stack.remove(stack.size() - 1);
                remover--;
            }
            stack.add(atual);
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < k; i++) {
            sb.append(stack.get(i));
        }

        return Long.parseLong(sb.toString());
    }

    public static void main(String[] args) throws IOException {
        String conteudo = Files.readString(Path.of("input.txt"));

        part01(conteudo);
        part02(conteudo);
    }
}
