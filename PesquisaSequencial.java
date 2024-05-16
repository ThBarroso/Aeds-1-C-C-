import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;

public class PesquisaSequencial {
    public static void main(String args[]){
        String codigo=MyIO.readLine();
        String linha;
        List <String> lista_nomes = new ArrayList<>();
        String nome_lido;
        String vetor_temporario[];

        //Primeira Parte
        while(!codigo.equals("FIM")){
            try (BufferedReader br = new BufferedReader(new FileReader("/tmp/characters.csv"))) {
                linha=br.readLine();
                while((linha = br.readLine()) != null){
                    vetor_temporario=linha.split(";");
                    if(vetor_temporario[0].equals(codigo)){
                        lista_nomes.add(vetor_temporario[1]);
                    }
                }
                codigo=MyIO.readLine();
            }catch (IOException | NumberFormatException e) {
                System.out.println("Erro ao ler arquivo ou formatar: " + e.getMessage());
            }
        }

        //Segunda Parte
        nome_lido=MyIO.readLine();
        Boolean encontrou=false;
        while(!nome_lido.equals("FIM")){
            for(String nome:lista_nomes){
                if(nome.equals(nome_lido)){
                    encontrou=true;
                    break;
                }
                encontrou=false;
            }        
            if(encontrou==true){
            MyIO.println("SIM");
            }
            else{
                MyIO.println("NAO");
            }
            nome_lido=MyIO.readLine();
        }
    }
}
